#ifndef __SIMPLECONTROL_H__
#define __SIMPLECONTROL_H__

#include <stdio.h>
#include <stdint.h>
#include "StreamControlIfStructs.h"

void StreamControlSyn(StreamControlControlRegistersT* AXI4Control, StreamControlControlRegistersT* Control,
                   StreamControlStatusRegistersT* AXI4Status, StreamControlStatusRegistersT* Status);

#endif
