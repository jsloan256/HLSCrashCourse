#ifndef __MULTIPLIER_H__
#define __MULTIPLIER_H__

#include <stdio.h>
#include <string.h>
#include <complex>
#include <hls_stream.h>
#include <ap_axi_sdata.h>
#include <hls_math.h>
#include "MultiplierStructs.h"

#define FP_TYPES  // Define to use fixed-point types. Un-define to use floats

#define SigGenWidth   16
#define SigGenInteger 4   // Integer portion of Multiplier output data type.
                          // SigGenInteger includes the sign, so the value range
                          // is -2^(SigGenInteger-1) to 2^(SigGenInteger-1)

typedef ap_fixed<SigGenWidth, SigGenInteger> SigGenT;
typedef hls::axis<SigGenT,0,0,0> SigGenAXIS;

#define SAMPLE_FREQUENCY    128000000.f
#define RADIAN_SREG_LENGTH  2
#define FRAMESIZE           16

void MultiplierSyn(MultiplierControlRegistersT<SigGenT,ap_uint<1> >* Control, hls::stream<SigGenAXIS>& Output);

class Multiplier
{
  public:
    Multiplier();
    void CalculateNextSample(MultiplierControlRegistersT<SigGenT,ap_uint<1> >* Control, hls::stream<SigGenAXIS>& Output);

  private:
    SigGenT RadianShiftRegister[RADIAN_SREG_LENGTH];
};

#endif
