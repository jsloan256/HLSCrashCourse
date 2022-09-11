#ifndef __MULTIPLIER_H__
#define __MULTIPLIER_H__

#include <stdio.h>
#include <string.h>
#include <complex>
#include <random>
#include <hls_stream.h>
#include <ap_axi_sdata.h>
#include <hls_math.h>

#define FRAMESIZE    16
#define INPUT_WIDTH   16
#define INPUT_INTEGER 4   // Integer portion of Multiplier output data type.
                          // INPUT_INTEGER includes the sign, so the value range
                          // is -2^(INPUT_INTEGER-1) to 2^(INPUT_INTEGER-1)

typedef ap_fixed<INPUT_WIDTH, INPUT_INTEGER> InputT;
typedef hls::axis<InputT,0,0,0> InputAXIS;

// Let HLS calculate the correct output bit width (and number of integer bits) based on
// the input type sizes and the operation to be performed
typedef typename hls::x_traits<InputT, InputT>::ADD_T OutputT;
typedef hls::axis<OutputT,0,0,0> OutputAXIS;

void MultiplierSyn(hls::stream<InputAXIS>& Input1, hls::stream<InputAXIS>& Input2, hls::stream<OutputAXIS>& Output);

class Multiplier
{
  public:
    Multiplier();
    void DoMultiplication(hls::stream<InputAXIS>& Input1, hls::stream<InputAXIS>& Input2, hls::stream<OutputAXIS>& Output);

  private:
};

#endif
