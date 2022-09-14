#include "Multiplier.h"

Multiplier::Multiplier()
{
}

void Multiplier::DoMultiplication(hls::stream<MultInputAXIS>& Input1, hls::stream<MultInputAXIS>& Input2, hls::stream<MultOutputAXIS>& Output)
{
  int Ndx;
  MultInputAXIS InVal1;
  MultInputAXIS InVal2;
  MultOutputAXIS OutVal;

  CalculateNextResult: for (Ndx=0; Ndx<FRAMESIZE; Ndx++)
  {
    #pragma HLS PIPELINE II=1 REWIND
    #pragma HLS BIND_OP variable=OutVal op=mul latency=3

    InVal1 = Input1.read();
    InVal2 = Input2.read();

    OutVal.data = InVal1.data * InVal2.data;

    Output.write(OutVal);
  }
}
