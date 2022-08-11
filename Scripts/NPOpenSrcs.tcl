set_part $PartName
set_property target_language Verilog [current_project]
set_property simulator_language Verilo [current_project]
set_property default_lib work [current_project]
set_property source_mgmt_mode All [current_project]
set_property ip_repo_paths $IpRepos [current_project]
if {[info exists BoardName]} {
  set_property "board_part" $BoardName [current_project]
}

update_ip_catalog

read_verilog [glob $HdlFolder/*.verilog]
#read_vhdl -library work [glob $HdlFolder/*.vhd]
#read_vhdl -library work [glob $WrapFolder/*.vhd]
read_ip [glob $XciFolders/*.xci]
#read_bd [glob $BdFolder/*.bd]

read_xdc [glob $ConstrFolder/*.xdc]
