#ifndef __SIGNALGENERATOR_H__
#define __SIGNALGENERATOR_H__

#include <stdio.h>
#include <string.h>
#include <complex>
#include <hls_stream.h>
#include <ap_axi_sdata.h>
#include <hls_math.h>
#include <utils/x_hls_traits.h>
#include "Types.h"

void SignalGeneratorControlSyn(SignalGeneratorControlRegistersT<float,uint32_t>* AXI4Control, SignalGeneratorControlRegistersT<FixedPointT,ap_uint<1> >* Control);
void SignalGeneratorSyn(SignalGeneratorControlRegistersT<FixedPointT,ap_uint<1> >* Control, hls::stream<DA3AXIS>& Output);

// #define SAMPLE_PERIOD 0.0000000078125
#define SAMPLE_FREQUENCY 128000000.f
#define VREF             2.5f
#define COUNT_PER_VOLT   65535.f / VREF     // 65535 because ADC is 16 bit
                                            // VRef on Digilent PA3 is 2.5V
#define DC_OFFSET        VREF / 2.f

#define RADIAN_SREG_LENGTH  2
#define FRAMESIZE           16

class SignalGenerator
{
  public:
    SignalGenerator();
    void CalculateNextSample(SignalGeneratorControlRegistersT<FixedPointT,ap_uint<1> >* Control, hls::stream<DA3AXIS>& Output);

  private:
    FixedPointT RadianShiftRegister[RADIAN_SREG_LENGTH];
};

#endif