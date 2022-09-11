#ifndef __SIGNALGENERATOR_H__
#define __SIGNALGENERATOR_H__

#include <stdio.h>
#include <string.h>
#include <complex>
#include <hls_stream.h>
#include <ap_axi_sdata.h>
#include <hls_math.h>
#include "SignalGeneratorStructs.h"

#define OUTPUT_WIDTH   16
#define OUTPUT_INTEGER 4  // Integer portion of SignalGenerator output data type.
                          // OUTPUT_INTEGER includes the sign, so the value range
                          // is -2^(OUTPUT_INTEGER-1) to 2^(OUTPUT_INTEGER-1)

typedef ap_fixed<OUTPUT_WIDTH, OUTPUT_INTEGER> OutputT;
typedef hls::axis<OutputT,0,0,0> OutputAXIS;

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
