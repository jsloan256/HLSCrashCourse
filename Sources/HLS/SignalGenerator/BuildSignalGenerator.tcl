open_project -reset SignalGeneratorProject
set_top SignalGeneratorSyn
add_files SignalGeneratorSyn.cpp
add_files SignalGenerator.cpp
add_files -tb SignalGeneratorTB.cpp

open_solution -reset solution1 -flow_target vivado
set_part  {xc7z010clg400-1}
create_clock -period 128.0MHz -name default

csim_design

config_dataflow -default_channel fifo -fifo_depth 2
csynth_design

cosim_design -rtl verilog -trace_level all

export_design -rtl verilog -format ip_catalog -description "Signal generator" -vendor "tsc.com" -version "1.01" -display_name "SignalGenerator"

close_solution
close_project
exit
