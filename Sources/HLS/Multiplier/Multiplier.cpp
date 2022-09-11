#include "Multiplier.h"

Multiplier::Multiplier()
{
}

void Multiplier::DoMultiplication(hls::stream<InputAXIS>& Input1, hls::stream<InputAXIS>& Input2, hls::stream<OutputAXIS>& Output)
{
  int Ndx;
  InputAXIS InVal1;
  InputAXIS InVal2;
  OutputAXIS OutVal;

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
