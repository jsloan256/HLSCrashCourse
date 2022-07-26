puts "=================================================================="
puts " Restore Vivado project"
puts "=================================================================="

source ./NPSetSrcs.tcl

# Create the Vivado project
create_project -force $Design $ProjectDir -part $PartName

if {[info exists BoardName]} {
  set_property "board_part" $BoardName [current_project]
}

# Add files to the Vivado project
#add_files -norecurse $HdlFolder -fileset sources_1
add_files -norecurse $WrapFolder -fileset sources_1

#foreach XciFolder $XciFolders {
#  set XciFile [glob $XciFolder/*.xci]
#  add_files -norecurse $XciFile
#}

#add_files -norecurse $SimFolder -fileset sim_1
add_files -norecurse $ConstrFolder -fileset constrs_1
#add_files -norecurse $FloorplanConstrFolder -fileset constrs_1

# Configure the Vivado project
set_property target_language Verilog [current_project]
set_property ip_repo_paths $IpRepos [current_project]
update_ip_catalog

# Update the Xilinx-generated restore TCL for the Block Diagram to have a relative (rather than absolute) file path
set BdFile [list $BdFolder/top/top.bd]
if {[file exists $BdFile] == 0} {
  source ./RestoreBD.tcl
} else {
  puts "WARNING: Skipping BD restore. It already exists!";
  read_bd [glob $BdFolder/top/*.bd]
}

set_property top $Top [get_fileset sources_1]
set_property top $TopSim [get_fileset sim_1]

source ./AddGUICommand.tcl
