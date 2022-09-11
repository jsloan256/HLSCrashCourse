open_project -reset StreamControlProject
set_top StreamControlSyn
add_files StreamControlSyn.cpp
add_files -tb StreamControlTB.cpp

open_solution -reset Solution -flow_target vivado
set_part  {xc7z010clg400-1}
create_clock -period 32.0MHz -name default

csim_design

config_dataflow -default_channel fifo -fifo_depth 2
csynth_design

cosim_design -rtl verilog -trace_level none

export_design -rtl verilog -format ip_catalog -description "Simple GPIO" -vendor "jsloan256-on-github" -version "1.01" -display_name "Simple GPIO"

close_solution
close_project
exit
