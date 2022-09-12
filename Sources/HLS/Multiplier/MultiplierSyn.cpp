#include "Multiplier.h"

void MultiplierSyn(hls::stream<MultInputAXIS>& Input1, hls::stream<MultInputAXIS>& Input2, hls::stream<MultOutputAXIS>& Output)
{
  #pragma HLS DATAFLOW
  #pragma HLS INTERFACE axis register port=Input1
  #pragma HLS INTERFACE axis register port=Input2
  #pragma HLS INTERFACE axis register port=Output

  static Multiplier AMultiplier;

  AMultiplier.DoMultiplication(Input1, Input2, Output);
}
