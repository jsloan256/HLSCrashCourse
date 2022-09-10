#include "SignalGenerator.h"

#define SIMULATION_LENGTH 128

void CalculateSignalGeneratorControlRegisters(float Frequency, float Vp, SignalGeneratorControlRegistersT<float, uint32_t>* AXI4Control)
{
  AXI4Control->Vp = Vp;
  AXI4Control->RadiansPerSample = ((Frequency / SAMPLE_FREQUENCY) * M_PI);

  printf("Setting Vp to %f\n", Vp, AXI4Control->Vp);
  printf("Setting frequency to %f Hz (%f RadiansPerSample)\n", Frequency, AXI4Control->RadiansPerSample);

  // Set maximum Vp based on ap_fixed type's I (SigGenInteger)
  if (AXI4Control->Vp < 0)
  {
    AXI4Control->Vp = 1.f;
    printf("Tried to set Vp to a negative failure, forced to one: %f\n", AXI4Control->Vp);
  }
  else if (AXI4Control->Vp > pow(2, (SigGenInteger-1)))
  {
    AXI4Control->Vp = pow(2, (SigGenInteger-1));
    printf("Capping Vp to 2^(SigGenInteger-1): %f\n", AXI4Control->Vp);
  }
}

int main()
{
  int i;
  int err = 0;
  SignalGeneratorControlRegistersT<float,uint32_t> AXI4Control;
  SignalGeneratorControlRegistersT<SigGenT, ap_uint<1> > Control;
  hls::stream<SigGenAXIS> Output;
  SigGenAXIS OutVal;
  #pragma HLS STREAM variable=Output depth=SIMULATION_LENGTH

  float Frequency = 4000000.f;  // 4 MHz
  float Vp = 6.f;               // Range will be -6.0 to 6.0

  CalculateSignalGeneratorControlRegisters(Frequency, Vp, &AXI4Control);

  // Convert AXIControl registers to Control registers (from 32bit ANSI types to HLS types)
  Control.RadiansPerSample = (SigGenT) AXI4Control.RadiansPerSample;
  Control.Vp               = (SigGenT) AXI4Control.Vp;

  printf("\nRunning UUT\n");
  for (i=0; i<SIMULATION_LENGTH/FRAMESIZE; i++)
  {
    SignalGeneratorSyn(&Control, Output);
  }

  // TODO: Add output data checking
  printf("OutVal\n");
  while (!Output.empty())
  {
    OutVal = Output.read();
    printf("%f\n", OutVal.data.to_float());
  }

  SigGenT temp;

  temp.range() = 0x8000;
  printf("temp = %f\n", temp.to_float());
  temp.range() = 0x7FFF;
  printf("temp = %f\n", temp.to_float());

  err = 0;

  return err;
}
