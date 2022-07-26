# This script DOES NOT WORK

source ./RestoreBD.tcl

read_bd [glob $BdFolder/*.bd]
update_compile_order -fileset sources_1
generate_target all [get_files $BdFolder/top.bd]
export_ip_user_files -of_objects [get_files $BdFolder/top.bd]
