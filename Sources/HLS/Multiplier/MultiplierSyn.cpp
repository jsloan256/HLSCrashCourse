#include "Multiplier.h"

void MultiplierSyn(MultiplierControlRegistersT<SigGenT,ap_uint<1> >* Control, hls::stream<SigGenAXIS>& Output)
{
  #pragma HLS DATAFLOW
  #pragma HLS INTERFACE ap_none register port=Control
  #pragma HLS disaggregate variable=Control
  #pragma HLS INTERFACE axis register port=Output

  static Multiplier AMultiplier;

  AMultiplier.CalculateNextSample(Control, Output);
}
