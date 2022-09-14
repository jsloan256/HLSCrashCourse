#include "SimpleGpio.h"

#define SIMULATION_LENGTH 128

int main()
{
  int i;
  int err = 0;

  SimpleGpioControlRegistersT AXI4Control;
  SimpleGpioControlRegistersT Control;

  SimpleGpioStatusRegistersT AXI4Status;
  SimpleGpioStatusRegistersT Status;

  std::default_random_engine gen{0xdeadbeef};
  std::uniform_int_distribution<int> dist(0, 0xFFFFFFFF);

  for (i=0; i<SIMULATION_LENGTH; i++)
  {
    // Use random values for the control registers (AXI4 side)
    AXI4Control.Register1 = dist(gen);
    AXI4Control.Register2 = dist(gen);
    AXI4Control.Register3 = dist(gen);

    // Use random value for the status registers (core side)
    Status.Register1 = dist(gen);
    Status.Register2 = dist(gen);
    Status.Register3 = dist(gen);

    SimpleGpioSyn(&AXI4Control, &Control, &AXI4Status, &Status);

    if (Control.Register1 != AXI4Control.Register1)
    {
      err++;
    }
    if (Control.Register2 != AXI4Control.Register2)
    {
      err++;
    }
    if (Control.Register3 != AXI4Control.Register3)
    {
      err++;
    }

    if (AXI4Status.Register1 != Status.Register1)
    {
      err++;
    }
    if (AXI4Status.Register2 != Status.Register2)
    {
      err++;
    }
    if (AXI4Status.Register3 != Status.Register3)
    {
      err++;
    }
  }

  return err;
}
