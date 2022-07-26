#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "xsimplegpiosyn.h"

#define BUS_NAME        "platform"

struct SimpleGpioControlRegistersT
{
  uint32_t Register1;
  uint32_t Register2;
  uint32_t Register3;
};

struct SimpleGpioStatusRegistersT
{
  uint32_t Register1;
  uint32_t Register2;
  uint32_t Register3;
};

void ParseArgs(int argc, char *argv[], SimpleGpioControlRegistersT* SimpleGpioControlRegisters);
static void Usage(void);

int main(int argc, char *argv[])
{
  SimpleGpioControlRegistersT* SimpleGpioControlRegisters;
  SimpleGpioStatusRegistersT* SimpleGpioStatusRegisters;
  XSimplegpiosyn SimpleGpioLoc;

  printf("simplegpio-example\n");

  // Initialize SimpleGpio interface
  printf("Initializing SimpleGpioSyn Cfg Block\n");
  if (XSimplegpiosyn_Initialize(&SimpleGpioLoc, "SimpleGpioSyn") != XST_SUCCESS)
  {
    printf("SimpleGpioSyn initialization FAILED\n");
    return 1;
  }
  else
  {
    printf("SimpleGpioControlSyn BaseAddress = 0x%016lX\n", SimpleGpioLoc.Axi4bus_BaseAddress);
    SimpleGpioControlRegisters = (SimpleGpioControlRegistersT*) (SimpleGpioLoc.Axi4bus_BaseAddress + XSIMPLEGPIOSYN_AXI4BUS_ADDR_AXI4CONTROL_DATA);
    SimpleGpioStatusRegisters = (SimpleGpioStatusRegistersT*) (SimpleGpioLoc.Axi4bus_BaseAddress + XSIMPLEGPIOSYN_AXI4BUS_ADDR_AXI4STATUS_DATA);
  }

  // Set the control registers based on the command line arguments
  ParseArgs(argc, argv, SimpleGpioControlRegisters);

  // Print the status registers
  printf("Status Register1 = 0x%08X\n", SimpleGpioStatusRegisters->Register1);
  printf("Status Register2 = 0x%08X\n", SimpleGpioStatusRegisters->Register2);
  printf("Status Register3 = 0x%08X\n", SimpleGpioStatusRegisters->Register3);

  return 0;
}

void ParseArgs(int argc, char *argv[], SimpleGpioControlRegistersT* SimpleGpioControlRegisters)
{
  int ch;
  float Val;

  while((ch = getopt(argc, argv, "?h1:2:3:")) != -1)
  {
    switch(ch)
    {
      case '1':
        SimpleGpioControlRegisters->Register1 = strtol(optarg, NULL, 16);
        break;

      case '2':
        SimpleGpioControlRegisters->Register2 = strtol(optarg, NULL, 16);
        break;

      case '3':
        SimpleGpioControlRegisters->Register3 = strtol(optarg, NULL, 16);
        break;

      case '?':
      case 'h':
        Usage();
        exit(0);
    }
  }
}

static void Usage(void)
{
  printf("simplegpio-example - Executable for SimpleGpio HLS core\n");
  printf("Compiled %s %s\n", __DATE__, __TIME__);

  printf("\t-1 <value in hex> - Value to write to Register1 (the six LSBs are connected to LEDs)\n");
  printf("\t-2 <value in hex> - Value to write to Register2\n");
  printf("\t-3 <value in hex> - Value to write to Register3\n");

  printf("\t-h|-? - Display this menu\n");
}
