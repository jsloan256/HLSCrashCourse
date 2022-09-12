#include "SignalGenerator.h"

#define SIMULATION_ITERATIONS 2
#define SIMULATION_LENGTH     128

void CalculateSignalGeneratorControlRegisters(float Frequency, float Vp, SignalGeneratorControlRegistersT<float, float, uint32_t>* AXI4Control)
{
  AXI4Control->Vp = Vp;
  AXI4Control->RadiansPerSample = ((Frequency/SAMPLE_FREQUENCY) * (2*M_PI));

  printf("Setting Vp to %f\n", Vp, AXI4Control->Vp);
  printf("Setting frequency to %f Hz (%f RadiansPerSample)\n", Frequency, AXI4Control->RadiansPerSample);

  // Set maximum Vp based on ap_fixed type's I (SIGGEN_OUTPUT_INTEGER)
  if (AXI4Control->Vp < 0)
  {
    AXI4Control->Vp = 1.f;
    printf("Tried to set Vp to a negative failure, forced to one: %f\n", AXI4Control->Vp);
  }
  else if (AXI4Control->Vp > pow(2, (SIGGEN_OUTPUT_INTEGER-1)))
  {
    AXI4Control->Vp = pow(2, (SIGGEN_OUTPUT_INTEGER-1));
    printf("Capping Vp to 2^(SIGGEN_OUTPUT_INTEGER-1): %f\n", AXI4Control->Vp);
  }
}

int main()
{
  int err = 0;
  int Ndx;
  int Iteration;
  SignalGeneratorControlRegistersT<float, float, uint32_t> AXI4Control;
  SignalGeneratorControlRegistersT<RadiansT, SigGenOutputT, ap_uint<1> > Control;
  hls::stream<SigGenOutputAXIS> Output;
  SigGenOutputAXIS OutVal;
  #pragma HLS STREAM variable=Output depth=SIMULATION_LENGTH
  int MinPeakNdx = 0;
  int MaxPeakNdx = 0;
  int OutputPeriod;
  float MaxOutVal = -999.9;
  float MinOutVal = 999.9;
  float OutputFrequency;
  float Frequency;
  float Vp;

  // A fixed seed is REQUIRED. If you don't provide one the reference data generated during csim (c++)
  // will not match the data generated during cosim (verilog)
  std::default_random_engine gen{0xdeadbeef};
  std::uniform_real_distribution<> dist1(1, (SAMPLE_FREQUENCY/32));
  std::uniform_real_distribution<> dist2(0, pow(2, (SIGGEN_OUTPUT_INTEGER-1)));

  for(Iteration=0; Iteration<SIMULATION_ITERATIONS; Iteration++)
  {
    Frequency = dist1(gen);
    Vp = dist2(gen);

    printf("\n");
    CalculateSignalGeneratorControlRegisters(Frequency, Vp, &AXI4Control);

    // Convert AXIControl registers to Control registers (from 32bit ANSI types to HLS types)
    Control.RadiansPerSample = (RadiansT) AXI4Control.RadiansPerSample;
    Control.Vp               = (SigGenOutputT) AXI4Control.Vp;

    printf("\nRunning UUT\n");
    for (Ndx=0; Ndx<SIMULATION_LENGTH/FRAMESIZE; Ndx++)
    {
      SignalGeneratorSyn(&Control, Output);
    }

    // Check the Output data stream
    Ndx = 0;
    while (!Output.empty())
    {
      OutVal = Output.read();

      // Store that minimum and maximum values of OutVal.data to be compared against the Vp (later)
      if (OutVal.data.to_float() > MaxOutVal)
      {
        MaxOutVal = OutVal.data.to_float();
        MaxPeakNdx = Ndx;
      }
      else if (OutVal.data.to_float() < MinOutVal)
      {
        MinOutVal = OutVal.data.to_float();
        MinPeakNdx = Ndx;
      }

      Ndx++;
    }

    // Round Vpp, MinOutVal, and MaxOutVal to the nearest tenth before checking
    Vp = round(Vp*10)/10;
    MinOutVal = round(MinOutVal*10)/10;
    MaxOutVal = round(MaxOutVal*10)/10;

    // Report an error if the maximum or minimum OutVal doesn't equal the fabs (ignoring signs, of course)
    printf("[Vp = %f, MinOutVal = %f, MaxOutVal=%f]\n", Vp, MinOutVal, MaxOutVal);
    if ((fabs(MinOutVal) != Vp) || (MaxOutVal != Vp))
    {
      printf("ERROR: Vp check failed (Vp = %f, MinOutVal = %f, MaxOutVal=%f)\n", Vp, MinOutVal, MaxOutVal);
      err++;
    }

    // Calculate the frequency of the output signal
    OutputPeriod = abs(MaxPeakNdx - MinPeakNdx) * 2;
    OutputFrequency = SAMPLE_FREQUENCY / OutputPeriod;
    // Round Frequency and OutputFrequency to the nearest 10s of kHz
    OutputFrequency = round(OutputFrequency/10000)*10000;
    Frequency = round(Frequency/10000)*10000;
    // Report an error if the output frequency doesn't match the frequency selected
    printf("[Frequency = %f, OutputFrequency = %f]\n", Frequency, OutputFrequency);
    if (OutputFrequency != Frequency)
    {
      printf("ERROR: Frequency check failed (Frequency = %f, OutputFrequency = %f)\n", Frequency, OutputFrequency);
      err++;
    }
  }

  return err;
}
