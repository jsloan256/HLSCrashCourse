#include "SignalGenerator.h"

#define SIMULATION_LENGTH 128

void CalculateSignalGeneratorControlRegisters(float Frequency, float Power, SignalGeneratorControlRegistersT<float, uint32_t>* AXI4Control)
{
//   float Vpp;
//   float RadiansPerSample;

  // Convert power in dBm to volts
  AXI4Control->Vpp = 2.f * sqrt(2.f) * sqrt(pow(10.f, Power/10.f) / 20.f);
  AXI4Control->RadiansPerSample = ((Frequency / SAMPLE_FREQUENCY) * M_PI);

  printf("Setting power to %f dBm (%f Vpp)\n", Power, AXI4Control->Vpp);
  printf("Setting frequency to %f Hz (%f RadiansPerSample)\n", Frequency, AXI4Control->RadiansPerSample);

  if (AXI4Control->Vpp > VREF/2.f)
  {
    AXI4Control->Vpp = VREF / 2.f;
    printf("Capping Vpp to VREF/2: %f\n", AXI4Control->Vpp);
  }
}

int main()
{
  int i;
  int err = 0;
  SignalGeneratorControlRegistersT<float,uint32_t> AXI4Control;
  SignalGeneratorControlRegistersT<FixedPointT, ap_uint<1> > Control;
  hls::stream<DA3AXIS> Output;
  DA3AXIS OutVal;
  #pragma HLS STREAM variable=Output depth=SIMULATION_LENGTH

  float Frequency = 4000000.f;      // 4 MHz
  float Power = 6.f;                // 6 dBm;

  CalculateSignalGeneratorControlRegisters(Frequency, Power, &AXI4Control);

  // Convert AXIControl regsiters to Control registers (from 32bit ANSI types to HLS types)
  Control.RadiansPerSample = (FixedPointT) AXI4Control.RadiansPerSample;
  Control.Vpp              = (FixedPointT) AXI4Control.Vpp;

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
    printf("%d\n", UINT( OutVal.data ));
  }

  err = 0;

  return err;
}
