open_project -reset SignalGeneratorProject
set_top SignalGeneratorSyn
add_files SignalGeneratorSyn.cpp
add_files SignalGenerator.cpp
add_files -tb SignalGeneratorTB.cpp
#add_files -tb SignalGeneratorControlSyn.cpp

puts "=================================================================="
puts " Creating Solution "
puts "=================================================================="
open_solution -reset solution1 -flow_target vivado
set_part  {xc7z010clg400-1}
create_clock -period 128.0MHz -name default

puts "=================================================================="
puts " Starting C Simulation"
puts "=================================================================="
csim_design
puts "=================================================================="
puts "Starting C Synthesis"
puts "=================================================================="
config_dataflow -default_channel fifo -fifo_depth 2
config_rtl -reset_level low -reset all
csynth_design
puts "=================================================================="
puts "Starting Co-simulation"
puts "=================================================================="
cosim_design -rtl verilog -trace_level all
puts "=================================================================="
puts "Starting Export to IP Core"
puts "=================================================================="
export_design -rtl verilog -format ip_catalog -description "Signal generator" -vendor "tsc.com" -version "1.01" -display_name "SignalGenerator"

close_solution
close_project
exit
