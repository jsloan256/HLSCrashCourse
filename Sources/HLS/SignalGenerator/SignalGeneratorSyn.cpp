#include "SignalGenerator.h"

void SignalGeneratorSyn(SignalGeneratorControlRegistersT<FixedPointT,ap_uint<1> >* Control, hls::stream<DA3AXIS>& Output)
{
  #pragma HLS DATAFLOW
  #pragma HLS INTERFACE ap_none register port=Control
  #pragma HLS disaggregate variable=Control
  #pragma HLS INTERFACE axis register port=Output

  static SignalGenerator ASignalGenerator;

  ASignalGenerator.CalculateNextSample(Control, Output);
}