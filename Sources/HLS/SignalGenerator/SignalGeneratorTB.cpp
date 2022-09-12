#include "SignalGenerator.h"

#define SIMULATION_LENGTH 128

void CalculateSignalGeneratorControlRegisters(float Frequency, float Vp, SignalGeneratorControlRegistersT<float, uint32_t>* AXI4Control)
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
  SignalGeneratorControlRegistersT<float,uint32_t> AXI4Control;
  SignalGeneratorControlRegistersT<SigGenOutputT, ap_uint<1> > Control;
  hls::stream<SigGenOutputAXIS> Output;
  SigGenOutputAXIS OutVal;
  #pragma HLS STREAM variable=Output depth=SIMULATION_LENGTH
  int PeakNdx1 = 0;
  int PeakNdx2 = 0;
  float MaxOutVal = -999.9;
  float MinOutVal = 999.9;
  float OutputFrequency;

  float Frequency = 4000000.f;  // 4 MHz
  float Vp = 6.f;               // Range will be -6.0 to 6.0

  CalculateSignalGeneratorControlRegisters(Frequency, Vp, &AXI4Control);

  // Convert AXIControl registers to Control registers (from 32bit ANSI types to HLS types)
  Control.RadiansPerSample = (SigGenOutputT) AXI4Control.RadiansPerSample;
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
    }
    else if (OutVal.data.to_float() < MinOutVal)
    {
      MinOutVal = OutVal.data.to_float();
    }

    // Record the last two Ndx values where OutVal.data == Vp to calculate the period of OutVal(s)
    if (OutVal.data.to_float() == Vp)
    {
      PeakNdx2 = PeakNdx1;
      PeakNdx1 = Ndx;
    }

    // printf("%f\n", OutVal.data.to_float());
    Ndx++;
  }

  // Report an error if the maximum or minimum OutVal doesn't equal the fabs (ignoring signs, of course)
  if ((fabs(MinOutVal) != Vp) || (MaxOutVal != Vp))
  {
    printf("ERROR: Vp check failed (Vp = %f, MinOutVal = %f, MaxOutVal=%f\n", Vp, MinOutVal, MaxOutVal);
    err++;
  }

  // Report an error if the output frequency doesn't match the frequency selected
  OutputFrequency = SAMPLE_FREQUENCY / (PeakNdx1 - PeakNdx2);
  if (OutputFrequency != Frequency)
  {
    printf("ERROR: Frequency check failed (Frequency = %f, OutputFrequency = %f)\n", Frequency, OutputFrequency);
    err++;
  }

  return err;
}
