#include "StreamControl.h"

#define SIMULATION_ITERATIONS 128

int main()
{
  int i;
  int err = 0;
  float OutputResolution = pow(2, -(SIGGEN_OUTPUT_WIDTH - SIGGEN_OUTPUT_INTEGER));

  SignalGeneratorControlRegistersT<float, float, uint32_t> AXI4Control1;
  SignalGeneratorControlRegistersT<RadiansT, SigGenOutputT, ap_uint<1> > Control1;

  SignalGeneratorControlRegistersT<float, float, uint32_t> AXI4Control2;
  SignalGeneratorControlRegistersT<RadiansT, SigGenOutputT, ap_uint<1> > Control2;

  // A fixed seed is REQUIRED. If you don't provide one the reference data generated during csim (c++)
  // will not match the data generated during cosim (verilog)

  // Set random generator range for Vp
  std::default_random_engine gen{0xdeadbeef};
  std::uniform_real_distribution<> dist(0, pow(2, (SIGGEN_OUTPUT_INTEGER-1)));

  // Set random generator range for RadiansPerSample
  std::uniform_real_distribution<> dist2(0, 6.283f);

  // Set random generator range for StartSG
  std::uniform_real_distribution<> dist3(0, 1.999f);

  for (i=0; i<SIMULATION_ITERATIONS; i++)
  {
    // Use random values for each Signal Generator #1 control register
    AXI4Control1.Vp = dist(gen);
    AXI4Control1.RadiansPerSample = dist2(gen);
    AXI4Control1.StartSG = (int) dist3(gen);

    // Use random values for each Signal Generator #2 control register
    AXI4Control2.Vp = dist(gen);
    AXI4Control2.RadiansPerSample = dist2(gen);
    AXI4Control2.StartSG = (int) dist3(gen);

    StreamControlSyn(&AXI4Control1, &Control1, &AXI4Control2, &Control2);

    // Check SignalGenerator #1's registers
    if ((Control1.Vp.to_float() < (AXI4Control2.Vp + OutputResolution))
      && (Control1.Vp.to_float() > (AXI4Control2.Vp - OutputResolution)))
    {
      printf("ERROR: Unexpected output value (Control1.Vp = %f, AXI4Control1.Vp = %f)\n",
        Control1.Vp.to_float(), AXI4Control1.Vp);
    }

    if ((Control1.RadiansPerSample.to_float() < (AXI4Control2.RadiansPerSample + OutputResolution))
      && (Control1.RadiansPerSample.to_float() > (AXI4Control2.RadiansPerSample - OutputResolution)))
    {
      printf("ERROR: Unexpected output value (Control1.RadiansPerSample = %f, AXI4Control1.RadiansPerSample = %f)\n",
        Control1.RadiansPerSample.to_float(), AXI4Control1.RadiansPerSample);
    }

    if (Control1.StartSG.to_uint() != (AXI4Control1.StartSG & 0x00000001))
    {
      printf("ERROR: Unexpected output value (Control1.StartSG = %f, AXI4Control1.StartSG = %f)\n",
        Control1.StartSG.to_uint(), AXI4Control1.StartSG);
    }

    // Check SignalGenerator #2's registers
    if ((Control2.Vp.to_float() < (AXI4Control2.Vp + OutputResolution))
      && (Control2.Vp.to_float() > (AXI4Control2.Vp - OutputResolution)))
    {
      printf("ERROR: Unexpected output value (Control2.Vp = %f, AXI4Control2.Vp = %f)\n",
        Control2.Vp.to_float(), AXI4Control2.Vp);
    }

    if ((Control2.RadiansPerSample.to_float() < (AXI4Control2.RadiansPerSample + OutputResolution))
      && (Control2.RadiansPerSample.to_float() > (AXI4Control2.RadiansPerSample - OutputResolution)))
    {
      printf("ERROR: Unexpected output value (Control2.RadiansPerSample = %f, AXI4Control2.RadiansPerSample = %f)\n",
        Control2.RadiansPerSample.to_float(), AXI4Control2.RadiansPerSample);
    }

    if (Control2.StartSG.to_uint() != (AXI4Control2.StartSG & 0x00000001))
    {
      printf("ERROR: Unexpected output value (Control2.StartSG = %f, AXI4Control2.StartSG = %f)\n",
        Control2.StartSG.to_uint(), AXI4Control2.StartSG);
    }
  }

  return err;
}
