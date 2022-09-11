#ifndef __SIGNALGENERATOR_H__
#define __SIGNALGENERATOR_H__

#include <stdio.h>
#include <string.h>
#include <complex>
#include <hls_stream.h>
#include <ap_axi_sdata.h>
#include <hls_math.h>
#include "SignalGeneratorTypes.h"

#define SAMPLE_FREQUENCY    128000000.f
#define RADIAN_SREG_LENGTH  2
#define FRAMESIZE           16

void SignalGeneratorSyn(SignalGeneratorControlRegistersT<OutputT,ap_uint<1> >* Control, hls::stream<OutputAXIS>& Output);

class SignalGenerator
{
  public:
    SignalGenerator();
    void CalculateNextSample(SignalGeneratorControlRegistersT<OutputT,ap_uint<1> >* Control, hls::stream<OutputAXIS>& Output);

  private:
    OutputT RadianShiftRegister[RADIAN_SREG_LENGTH];
};

#endif
