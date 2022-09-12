#include "SignalGenerator.h"

SignalGenerator::SignalGenerator()
{
  int Ndx;

  for (Ndx=0; Ndx<RADIAN_SREG_LENGTH; Ndx++)
  {
    RadianShiftRegister[Ndx] = 0.f;
  }
}

void SignalGenerator::CalculateNextSample(SignalGeneratorControlRegistersT<RadiansT, SigGenOutputT,ap_uint<1> >* Control, hls::stream<SigGenOutputAXIS>& Output)
{
  int Ndx;
  SigGenOutputAXIS OutVal;
  RadiansT CurrentRadian;
  RadiansT NextRadian;
  RadiansT NextRadianLimited;
  RadiansT Pi = M_PI;
  RadiansT TwoPi = 2 * M_PI;
  SigGenOutputT SineResult;

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
