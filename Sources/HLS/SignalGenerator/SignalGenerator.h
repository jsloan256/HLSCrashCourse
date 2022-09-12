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

void SignalGeneratorSyn(SignalGeneratorControlRegistersT<SigGenOutputT,ap_uint<1> >* Control, hls::stream<SigGenOutputAXIS>& Output);

class SignalGenerator
{
  public:
    SignalGenerator();
    void CalculateNextSample(SignalGeneratorControlRegistersT<SigGenOutputT,ap_uint<1> >* Control, hls::stream<SigGenOutputAXIS>& Output);

  private:
    SigGenOutputT RadianShiftRegister[RADIAN_SREG_LENGTH];
};

#endif
