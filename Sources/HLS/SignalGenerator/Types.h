#ifndef __TYPES_H__
#define __TYPES_H__

#include <stdio.h>
#include <string.h>
// #include <math.h>
#ifdef __cplusplus
#include <complex>
#else
#include <stdint.h>
#endif

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

// TODO: Consider making the DC offset controllable
template<typename Tf, typename T1>
struct SignalGeneratorControlRegistersT
{
  Tf RadiansPerSample;
  Tf Vpp;
  T1 StartSG;
};

#define DA3_W 16              // Digilent PA3 has a 16 bit ADC
typedef hls::axis<ap_uint<DA3_W>,0,0,0> DA3AXIS;

#endif