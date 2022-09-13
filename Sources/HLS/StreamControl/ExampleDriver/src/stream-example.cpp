#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "xstreamcontrolsyn.h"

#define BUS_NAME        "platform"

// Copy of struct from SignalGenerator core (removed template)
struct SignalGeneratorControlRegistersT
{
  float RadiansPerSample;
  float Vp;
  uint32_t StartSG;
};

void ParseArgs(int argc, char *argv[], SignalGeneratorControlRegistersT* Control1, SignalGeneratorControlRegistersT* Control2);
static void Usage(void);

int main(int argc, char *argv[])
{
  SignalGeneratorControlRegistersT* SignalGenerator1ControlRegisters;
  SignalGeneratorControlRegistersT* SignalGenerator2ControlRegisters;
  XStreamcontrolsyn StreamControlLoc;

  printf("stream-example\n");

  // Initialize StreamControl interface
  printf("Initializing StreamControlSyn Cfg Block\n");
  if (XStreamcontrolsyn_Initialize(&StreamControlLoc, "StreamControlSyn") != XST_SUCCESS)
  {
    printf("StreamControlSyn initialization FAILED\n");
    return 1;
  }
  else
  {
    printf("StreamControlControlSyn BaseAddress = 0x%016lX\n", StreamControlLoc.Axi4bus_BaseAddress);

    SignalGenerator1ControlRegisters = (SignalGeneratorControlRegistersT*) (StreamControlLoc.Axi4bus_BaseAddress + XSTREAMCONTROLSYN_AXI4BUS_ADDR_AXI4CONTROL1_DATA);
    SignalGenerator2ControlRegisters = (SignalGeneratorControlRegistersT*) (StreamControlLoc.Axi4bus_BaseAddress + XSTREAMCONTROLSYN_AXI4BUS_ADDR_AXI4CONTROL2_DATA);
  }

  // Set the control registers based on the command line arguments
  ParseArgs(argc, argv, SignalGenerator1ControlRegisters, SignalGenerator2ControlRegisters);

  // Start the SignalGenerator cores
  SignalGenerator1ControlRegisters->StartSG = 1;
  SignalGenerator2ControlRegisters->StartSG = 1;

  return 0;
}

// CalculateSignalGeneratorControlRegisters() and the following defines copied from SignalGenerator core
#define SAMPLE_FREQUENCY    32000000.f
#define SIGGEN_OUTPUT_INTEGER 4
void CalculateSignalGeneratorControlRegisters(float Frequency, float Vp, SignalGeneratorControlRegistersT* AXI4Control)
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

void ParseArgs(int argc, char *argv[], SignalGeneratorControlRegistersT* Control1, SignalGeneratorControlRegistersT* Control2)
{
  int ch;

  float SigGen1Vp = 1.f;
  float SigGen1Frequency = 1000000.f;
  float SigGen2Vp = 1.f;
  float SigGen2Frequency = 1000000.f;

  while((ch = getopt(argc, argv, "?hv:f:V:F:")) != -1)
  {
    switch(ch)
    {
      case 'v':
        SigGen1Vp = strtof(optarg, NULL);
        break;

      case 'f':
        SigGen1Frequency = strtof(optarg, NULL);
        break;

      case 'V':
        SigGen2Vp = strtof(optarg, NULL);
        break;

      case 'F':
        SigGen2Frequency = strtof(optarg, NULL);
        break;

      case '?':
      case 'h':
        Usage();
        exit(0);
    }
  }

  CalculateSignalGeneratorControlRegisters(SigGen1Frequency, SigGen1Vp, Control1);
  CalculateSignalGeneratorControlRegisters(SigGen2Frequency, SigGen2Vp, Control2);
}

static void Usage(void)
{
  printf("stream-example - Executable for SignalGenerator (x2) and Multiplier cores\n");
  printf("Compiled %s %s\n", __DATE__, __TIME__);

  printf("\t-v <float> - SignalGenerator #1 Vp (0 to 8.0, default = 1.0)\n");
  printf("\t-f <float> - SignalGenerator #2 Frequency in Hz (maximum is 16 MHz, default is 1000000.0 Hz\n");
  printf("\t-V <float> - SignalGenerator #2 Vp (0 to 8.0, default = 1.0)\n");
  printf("\t-f <float> - SignalGenerator #2 Frequency in Hz (maximum is 16 MHz, default is 1000000.0 Hz\n");

  printf("\t-h|-? - Display this menu\n");
}
