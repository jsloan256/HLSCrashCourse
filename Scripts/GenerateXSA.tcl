# Set project defines
source ./NPSetSrcs.tcl

# Delete old export XSA if it exists
file delete -force $ExportFolder/top_wrapper.xsa

# Open the Vivado project
open_project ../Vivado/$Design
update_compile_order -fileset sources_1

if {[catch {current_project} result ]} {
  error "ERROR: Failed to open Vivado project"
}

# Synthesize the design
launch_runs synth_1 -jobs $NumThreads
wait_on_run synth_1
if {[get_property PROGRESS [get_runs synth_1]] != "100%"} {   
  error "ERROR: synth_1 failed"
}

# Implement the design
launch_runs impl_1 -to_step write_bitstream -jobs $NumThreads
wait_on_run impl_1
if {[get_property PROGRESS [get_runs impl_1]] != "100%"} {   
  error "ERROR: impl_1 failed"   
}

# Check to see if the design met timing
set ImplementationWNS [get_property STATS.WNS [get_runs impl_1]]
set ImplementationWHS [get_property STATS.WHS [get_runs impl_1]]
if [expr {$ImplementationWNS < 0.0 || $ImplementationWHS < 0.0}] {
  error "ERROR: Failed to meet timing"
}

# Export XSA
write_hw_platform -fixed -include_bit -force -file $ExportFolder/top_wrapper.xsa
if {[file exists $ExportFolder/top_wrapper.xsa] == 0} {
  error "ERROR: Failed to generate XSA"
}
puts "Successfully generated the XSA (WNS = ${ImplementationWNS}, WHS =${ImplementationWHS})"
