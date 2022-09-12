#ifndef __SIMPLECONTROL_H__
#define __SIMPLECONTROL_H__

#include <stdio.h>
#include <stdint.h>
#include <random>
#include <hls_stream.h>
#include <ap_axi_sdata.h>
#include <hls_math.h>

#include "../SignalGenerator/SignalGeneratorTypes.h"

void StreamControlSyn(SignalGeneratorControlRegistersT<float, uint32_t>* AXI4Control1, SignalGeneratorControlRegistersT<SigGenOutputT, ap_uint<1> >* Control1,
                      SignalGeneratorControlRegistersT<float, uint32_t>* AXI4Control2, SignalGeneratorControlRegistersT<SigGenOutputT, ap_uint<1> >* Control2);

#endif
