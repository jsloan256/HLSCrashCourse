#ifndef __MULTIPLIERTYPES_H__
#define __MULTIPLIERTYPES_H__

#define MULT_INPUT_WIDTH   16
#define MULT_INPUT_INTEGER 4  // Integer portion of Multiplier output data type.
                              // MULT_INPUT_INTEGER includes the sign, so the value range
                              // is -2^(MULTI_INPUT_INTEGER-1) to 2^(MULT_INPUT_INTEGER-1)

typedef ap_fixed<MULT_INPUT_WIDTH, MULT_INPUT_INTEGER> MultInputT;
typedef hls::axis<MultInputT,0,0,0> MultInputAXIS;

// Let HLS calculate the correct output bit width (and number of integer bits) based on
// the input type sizes and the operation to be performed
typedef typename hls::x_traits<MultInputT, MultInputT>::ADD_T MultOutputT;
typedef hls::axis<MultOutputT,0,0,0> MultOutputAXIS;

#endif
