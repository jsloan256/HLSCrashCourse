#include "Multiplier.h"

void MultiplierSyn(hls::stream<InputAXIS>& Input1, hls::stream<InputAXIS>& Input2, hls::stream<OutputAXIS>& Output)
{
  #pragma HLS DATAFLOW
  #pragma HLS INTERFACE axis register port=Input1
  #pragma HLS INTERFACE axis register port=Input2
  #pragma HLS INTERFACE axis register port=Output

  static Multiplier AMultiplier;

  AMultiplier.DoMultiplication(Input1, Input2, Output);
}
