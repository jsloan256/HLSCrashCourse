#include "SignalGenerator.h"

void SignalGeneratorControlSyn(SignalGeneratorControlRegistersT<float,uint32_t>* AXI4Control, SignalGeneratorControlRegistersT<FixedPointT,ap_uint<1> >* Control)
{
#pragma HLS DATAFLOW
#pragma HLS INTERFACE s_axilite register port=AXI4Control bundle=AXI4Bus
#pragma HLS INTERFACE ap_none register port=Control
#pragma HLS disaggregate variable=Control
#pragma HLS disaggregate variable=Control->RadiansPerSample
#pragma HLS disaggregate variable=Control->Vpp
#pragma HLS disaggregate variable=Control->StartSG

  // Read Control registers
  Control->RadiansPerSample = (FixedPointT) AXI4Control->RadiansPerSample;
  Control->Vpp              = (FixedPointT) AXI4Control->Vpp;
  Control->StartSG          = AXI4Control->StartSG;

  // Write Status registers
}
