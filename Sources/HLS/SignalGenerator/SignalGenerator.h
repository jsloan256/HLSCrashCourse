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

#ifdef FP_TYPES
  #define FLT( var ) var.to_float()
  #define UINT( var ) var.to_uint()
  typedef ap_fixed<16, 4> FixedPointT;
//   typedef ap_fixed<16, 4, AP_RND, AP_SAT> FixedPointSatT;
  typedef ap_fixed<16, 4> FixedPointSatT;     // TODO: Improve behavior when Control-Vpp
                                              // saturates (line above causes odd behavior)
#else
  #define FLT( var ) var
  #define UINT( var ) var
  typedef float FixedPointT;
  typedef float FixedPointSatT;
#endif

#define DA3_W 16              // Digilent PA3 has a 16 bit ADC
typedef hls::axis<ap_uint<DA3_W>,0,0,0> DA3AXIS;

#define SAMPLE_FREQUENCY 128000000.f
#define VREF             2.5f
#define COUNT_PER_VOLT   65535.f / VREF     // 65535 because ADC is 16 bit
                                            // VRef on Digilent PA3 is 2.5V
#define DC_OFFSET        VREF / 2.f

#define RADIAN_SREG_LENGTH  2
#define FRAMESIZE           16

void SignalGeneratorSyn(SignalGeneratorControlRegistersT<FixedPointT,ap_uint<1> >* Control, hls::stream<DA3AXIS>& Output);

class SignalGenerator
{
  public:
    SignalGenerator();
    void CalculateNextSample(SignalGeneratorControlRegistersT<FixedPointT,ap_uint<1> >* Control, hls::stream<DA3AXIS>& Output);

  private:
    FixedPointT RadianShiftRegister[RADIAN_SREG_LENGTH];
};

#endif