#include "StreamControl.h"

void StreamControlSyn(StreamControlControlRegistersT* AXI4Control, StreamControlControlRegistersT* Control,
                   StreamControlStatusRegistersT* AXI4Status, StreamControlStatusRegistersT* Status)
{
#pragma HLS DATAFLOW

#pragma HLS INTERFACE s_axilite register port=AXI4Control bundle=AXI4Bus
#pragma HLS INTERFACE ap_none register port=Control
#pragma HLS disaggregate variable=Control

#pragma HLS INTERFACE s_axilite register port=AXI4Status bundle=AXI4Bus
#pragma HLS INTERFACE ap_none register port=Status
#pragma HLS disaggregate variable=Status

  // Set output Control register output ports from the AXI4 Control Registers
  Control->Register1 = AXI4Control->Register1;
  Control->Register2 = AXI4Control->Register2;
  Control->Register3 = AXI4Control->Register3;

  // Set AXI4 Status registers from the Status register port inputs
  AXI4Status->Register1 = Status->Register1;
  AXI4Status->Register2 = Status->Register2;
  AXI4Status->Register3 = Status->Register3;
}
