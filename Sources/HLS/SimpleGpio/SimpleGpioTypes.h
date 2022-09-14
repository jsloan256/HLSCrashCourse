#ifndef __SIMPLEGPIOIFTYPES_H__
#define __SIMPLEGPIOIFTYPES_H__

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

#endif
