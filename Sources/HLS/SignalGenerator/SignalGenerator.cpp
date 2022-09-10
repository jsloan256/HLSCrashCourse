#include "SignalGenerator.h"

// TODO: Add constructor argument (RadiansPerSample) to better initialize the shift register
SignalGenerator::SignalGenerator()
{
  int Ndx;

  for (Ndx=0; Ndx<RADIAN_SREG_LENGTH; Ndx++)
  {
    RadianShiftRegister[Ndx] = 0.f;
  }
}

void SignalGenerator::CalculateNextSample(SignalGeneratorControlRegistersT<FixedPointT,ap_uint<1> >* Control, hls::stream<DA3AXIS>& Output)
{
  int Ndx;
  DA3AXIS OutVal;
  FixedPointT CurrentRadian;
  FixedPointT NextRadian;
  FixedPointT NextRadianLimited;
  FixedPointT CountPerVolt = COUNT_PER_VOLT;
  FixedPointT Pi = M_PI;
  FixedPointT TwoPi = 2 * M_PI;
  FixedPointT DCOffset = DC_OFFSET;
  FixedPointT SineResult;
  FixedPointSatT OutputVoltage;
  FixedPointSatT OutputCount;

  #pragma HLS ARRAY_PARTITION variable=RadianShiftRegister complete dim=1

  CalculateNextSampleLoop: for (Ndx=0; Ndx<FRAMESIZE; Ndx++)
  {
    #pragma HLS PIPELINE II=1 REWIND

    // Pull oldest Radian value from shift register
    CurrentRadian = RadianShiftRegister[1];

    SineResult = hls::sin(CurrentRadian);
    OutputVoltage = Control->Vpp * SineResult + DCOffset;
    OutputCount = OutputVoltage * CountPerVolt;
    OutVal.data = OutputCount.range();

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

//     printf("CurrentRadian = %f\n", FLT(CurrentRadian));
//     printf("OutputVoltage = %f\n", FLT(OutputVoltage));
//     printf("OutVal.data = %s\n", OutVal.data.to_string(16).c_str());

    Output.write(OutVal);
  }
}