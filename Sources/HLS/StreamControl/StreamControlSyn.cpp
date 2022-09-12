#include "StreamControl.h"

void StreamControlSyn(SignalGeneratorControlRegistersT<float, uint32_t>* AXI4Control1, SignalGeneratorControlRegistersT<SigGenOutputT, ap_uint<1> >* Control1,
                      SignalGeneratorControlRegistersT<float, uint32_t>* AXI4Control2, SignalGeneratorControlRegistersT<SigGenOutputT, ap_uint<1> >* Control2)
{
  #pragma HLS DATAFLOW

  #pragma HLS INTERFACE s_axilite register port=AXI4Control1 bundle=AXI4Bus
  #pragma HLS INTERFACE ap_none register port=Control1
  #pragma HLS disaggregate variable=Control1

  #pragma HLS INTERFACE s_axilite register port=AXI4Control2 bundle=AXI4Bus
  #pragma HLS INTERFACE ap_none register port=Control2
  #pragma HLS disaggregate variable=Control2

  // Set output Control ports from the AXI4 Control registers (for SignalGenerator core #1)
  Control1->RadiansPerSample  = AXI4Control1->RadiansPerSample;
  Control1->Vp                = AXI4Control1->Vp;
  Control1->StartSG           = AXI4Control1->StartSG;

  // Set output Control ports from the AXI4 Control registers (for SignalGenerator core #2)
  Control2->RadiansPerSample  = AXI4Control2->RadiansPerSample;
  Control2->Vp                = AXI4Control2->Vp;
  Control2->StartSG           = AXI4Control2->StartSG;
}
