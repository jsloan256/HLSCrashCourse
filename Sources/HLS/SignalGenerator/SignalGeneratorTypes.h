#ifndef __SIGNALGENERATORTYPES_H__
#define __SIGNALGENERATORTYPES_H__

#define OUTPUT_WIDTH   16
#define OUTPUT_INTEGER 4  // Integer portion of SignalGenerator output data type.
                          // OUTPUT_INTEGER includes the sign, so the value range
                          // is -2^(OUTPUT_INTEGER-1) to 2^(OUTPUT_INTEGER-1)

typedef ap_fixed<OUTPUT_WIDTH, OUTPUT_INTEGER> OutputT;
typedef hls::axis<OutputT,0,0,0> OutputAXIS;

template<typename Tf, typename T1>
struct SignalGeneratorControlRegistersT
{
  Tf RadiansPerSample;
  Tf Vp;
  T1 StartSG;
};

#endif