#include "SimpleGpio.h"

int main()
{
  int i;
  int err = 0;

  SimpleGpioControlRegistersT AXI4Control;
  SimpleGpioControlRegistersT Control;

  SimpleGpioStatusRegistersT AXI4Status;
  SimpleGpioStatusRegistersT Status;

  AXI4Control.Register1 = 0x11;
  AXI4Control.Register2 = 0x22;
  AXI4Control.Register3 = 0x33;

  Status.Register1 = 0xAA;
  Status.Register2 = 0xBB;
  Status.Register3 = 0xCC;

  for (i=0; i<5; i++)
  {
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

    AXI4Control.Register1 += 1;
    AXI4Control.Register2 += 1;
    AXI4Control.Register3 += 1;

    Status.Register1 += 1;
    Status.Register2 += 1;
    Status.Register3 += 1;
  }

  return err;
}
