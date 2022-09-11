#include "Multiplier.h"

Multiplier::Multiplier()
{
  int Ndx;

  for (Ndx=0; Ndx<RADIAN_SREG_LENGTH; Ndx++)
  {
    RadianShiftRegister[Ndx] = 0.f;
  }
}

void Multiplier::CalculateNextSample(MultiplierControlRegistersT<SigGenT,ap_uint<1> >* Control, hls::stream<SigGenAXIS>& Output)
{
  int Ndx;
  SigGenAXIS OutVal;
  SigGenT CurrentRadian;
  SigGenT NextRadian;
  SigGenT NextRadianLimited;
  SigGenT Pi = M_PI;
  SigGenT TwoPi = 2 * M_PI;
  SigGenT SineResult;

  #pragma HLS ARRAY_PARTITION variable=RadianShiftRegister complete dim=1

  CalculateNextSampleLoop: for (Ndx=0; Ndx<FRAMESIZE; Ndx++)
  {
    #pragma HLS PIPELINE II=1 REWIND

    // Pull oldest Radian value from shift register
    CurrentRadian = RadianShiftRegister[1];

    // Calculate the new output value
    SineResult = hls::sin(CurrentRadian);
    OutVal.data = Control->Vp * SineResult;

    // Calculate the next radian value using the value calculated last time
    NextRadian = RadianShiftRegister[0] + Control->RadiansPerSample;

    if (NextRadian > TwoPi)
    {
      NextRadianLimited = NextRadian - TwoPi;
    }
    else
    {
      NextRadianLimited = NextRadian;
    }

    RadianShiftRegister[1] = RadianShiftRegister[0];
    RadianShiftRegister[0] = NextRadianLimited;

    Output.write(OutVal);
  }
}
