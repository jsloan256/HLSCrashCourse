#ifndef __SIMPLEGPIO_H__
#define __SIMPLEGPIO_H__

#include <stdio.h>
#include <stdint.h>
#include "SimpleGpioIfStructs.h"

void SimpleGpioSyn(SimpleGpioControlRegistersT* AXI4Control, SimpleGpioControlRegistersT* Control,
                   SimpleGpioStatusRegistersT* AXI4Status, SimpleGpioStatusRegistersT* Status);

#endif
