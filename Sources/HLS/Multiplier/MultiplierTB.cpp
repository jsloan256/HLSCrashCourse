#include "Multiplier.h"

#define SIMULATION_ITERATIONS 128

int main()
{
  int err = 0;
  int Ndx;
  hls::stream<MultInputAXIS> Input1;
  MultInputAXIS InVal1;
  hls::stream<MultInputAXIS> Input2;
  MultInputAXIS InVal2;
  hls::stream<MultOutputAXIS> Output;
  MultOutputAXIS OutVal;
  #pragma HLS STREAM variable=Input1 depth=SIMULATION_ITERATIONS
  #pragma HLS STREAM variable=Input2 depth=SIMULATION_ITERATIONS
  #pragma HLS STREAM variable=Output depth=SIMULATION_ITERATIONS

  MultOutputT OutRef[SIMULATION_ITERATIONS];

  // A fixed seed is REQUIRED. If you don't provide one the reference data generated during csim (c++)
  // will not match the data generated during cosim (verilog)
  std::default_random_engine gen{0xdeadbeef};
  // Set random data range based on the max and min input integer values
  // (eg. -8 to 8 for MULT_INPUT_INTEGER = 4)
  std::uniform_real_distribution<> dist(-pow(2, (MULT_INPUT_INTEGER-1)), pow(2, (MULT_INPUT_INTEGER-1)));
  for (Ndx=0; Ndx<SIMULATION_ITERATIONS; Ndx++)
  {
    // Load Input1 and Input2 with random data
    InVal1.data = (MultInputT) dist(gen);
    InVal2.data = (MultInputT) dist(gen);

    Input1.write(InVal1);
    Input2.write(InVal2);

    OutRef[Ndx] = InVal1.data * InVal2.data;
  }

  printf("\nRunning UUT\n");
  for (Ndx=0; Ndx<SIMULATION_ITERATIONS/FRAMESIZE; Ndx++)
  {
    MultiplierSyn(Input1, Input2, Output);
  }

  // Check the Output data stream
  Ndx = 0;
  while (!Output.empty())
  {
    OutVal = Output.read();

    if (OutVal.data != OutRef[Ndx])
    {
      printf("ERROR: Unexpected output value (OutRef[%d] = %f, OutVal = %f)\n", Ndx, OutRef[Ndx].to_float(), OutVal.data.to_float());
      err++;
    }

    Ndx++;
  }

  return err;
}
