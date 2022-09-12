#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "streamcontrolsyn.h"

#define BUS_NAME        "platform"

// Copy of struct from SignalGenerator core (removed template)
struct SignalGeneratorControlRegistersT
{
  unint32_t RadiansPerSample;
  unint32_t Vp;
  float StartSG;
};

// void ParseArgs(int argc, char *argv[], SimpleGpioControlRegistersT* SimpleGpioControlRegisters);
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

    SignalGenerator1ControlRegisters = (SignalGeneratorControlRegistersT*) (StreamControlLoc.Axi4bus_BaseAddress + XSTREAMCONTROLSYN_AXI4BUS_ADDR_AXI4CONTROL1_DATA;
    SignalGenerator2ControlRegisters = (SignalGeneratorControlRegistersT*) (StreamControlLoc.Axi4bus_BaseAddress + XSTREAMCONTROLSYN_AXI4BUS_ADDR_AXI4CONTROL2_DATA;
  }

  // Set the control registers based on the command line arguments
//   ParseArgs(argc, argv, StreamControlControlRegisters);

  // Print the status registers
//   printf("Status Register1 = 0x%08X\n", StreamControlStatusRegisters->Register1);
//   printf("Status Register2 = 0x%08X\n", StreamControlStatusRegisters->Register2);
//   printf("Status Register3 = 0x%08X\n", StreamControlStatusRegisters->Register3);

  return 0;
}

// void ParseArgs(int argc, char *argv[], SimpleGpioControlRegistersT* SimpleGpioControlRegisters)
// {
//   int ch;
//   float Val;
// 
//   while((ch = getopt(argc, argv, "?h1:2:3:")) != -1)
//   {
//     switch(ch)
//     {
//       case '1':
//         SimpleGpioControlRegisters->Register1 = strtol(optarg, NULL, 16);
//         break;
// 
//       case '2':
//         SimpleGpioControlRegisters->Register2 = strtol(optarg, NULL, 16);
//         break;
// 
//       case '3':
//         SimpleGpioControlRegisters->Register3 = strtol(optarg, NULL, 16);
//         break;
// 
//       case '?':
//       case 'h':
//         Usage();
//         exit(0);
//     }
//   }
// }
// 
// static void Usage(void)
// {
//   printf("simplegpio-example - Executable for SimpleGpio HLS core\n");
//   printf("Compiled %s %s\n", __DATE__, __TIME__);
// 
//   printf("\t-1 <value in hex> - Value to write to Register1 (the six LSBs are connected to LEDs)\n");
//   printf("\t-2 <value in hex> - Value to write to Register2\n");
//   printf("\t-3 <value in hex> - Value to write to Register3\n");
// 
//   printf("\t-h|-? - Display this menu\n");
// }
