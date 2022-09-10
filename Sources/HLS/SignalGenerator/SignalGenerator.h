#ifndef __SIGNALGENERATOR_H__
#define __SIGNALGENERATOR_H__

#include <stdio.h>
#include <string.h>
#include <complex>
#include <hls_stream.h>
#include <ap_axi_sdata.h>
#include <hls_math.h>
#include "SignalGeneratorStructs.h"

#define FP_TYPES  // Define to use fixed-point types. Un-define to use floats

#define SigGenWidth   16
#define SigGenInteger 4   // Integer portion of SignalGenerator output data type.
                          // SigGenInteger includes the sign, so the value range
                          // is -2^(SigGenInteger-1) to 2^(SigGenInteger-1)

typedef ap_fixed<SigGenWidth, SigGenInteger> SigGenT;
typedef hls::axis<SigGenT,0,0,0> SigGenAXIS;

#define SAMPLE_FREQUENCY    128000000.f
#define RADIAN_SREG_LENGTH  2
#define FRAMESIZE           16

void SignalGeneratorSyn(SignalGeneratorControlRegistersT<SigGenT,ap_uint<1> >* Control, hls::stream<SigGenAXIS>& Output);

class SignalGenerator
{
  public:
    SignalGenerator();
    void CalculateNextSample(SignalGeneratorControlRegistersT<SigGenT,ap_uint<1> >* Control, hls::stream<SigGenAXIS>& Output);

  private:
    SigGenT RadianShiftRegister[RADIAN_SREG_LENGTH];
};

#endif