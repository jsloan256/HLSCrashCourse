#ifndef __MULTIPLIER_H__
#define __MULTIPLIER_H__

#include <stdio.h>
#include <string.h>
#include <complex>
#include <random>
#include <hls_stream.h>
#include <ap_axi_sdata.h>
#include <hls_math.h>
#include "MultiplierTypes.h"

#define FRAMESIZE    16

void MultiplierSyn(hls::stream<MultInputAXIS>& Input1, hls::stream<MultInputAXIS>& Input2, hls::stream<MultOutputAXIS>& Output);

class Multiplier
{
  public:
    Multiplier();
    void DoMultiplication(hls::stream<MultInputAXIS>& Input1, hls::stream<MultInputAXIS>& Input2, hls::stream<MultOutputAXIS>& Output);

  private:
};

#endif
