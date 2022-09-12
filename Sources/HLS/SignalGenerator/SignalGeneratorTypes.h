#ifndef __SIGNALGENERATORTYPES_H__
#define __SIGNALGENERATORTYPES_H__

#define SIGGEN_OUTPUT_WIDTH   16
#define SIGGEN_OUTPUT_INTEGER 4   // Integer portion of SignalGenerator output data type.
                                  // SIGGEN_OUTPUT_INTEGER includes the sign, so the value range
                                  // is -2^(SIGGEN_OUTPUT_INTEGER-1) to 2^(SIGGEN_OUTPUT_INTEGER-1)

typedef ap_fixed<SIGGEN_OUTPUT_WIDTH, SIGGEN_OUTPUT_INTEGER> SigGenOutputT;
typedef hls::axis<SigGenOutputT,0,0,0> SigGenOutputAXIS;

typedef ap_fixed<32, 4> RadiansT;

template<typename Tr, typename Tf, typename T1>
struct SignalGeneratorControlRegistersT
{
  Tr RadiansPerSample;
  Tf Vp;
  T1 StartSG;
};

#endif