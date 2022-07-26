set CurrentProjectDirectory [get_property DIRECTORY [current_project] ]
cd $CurrentProjectDirectory

cd ../Scripts
source ./NPSetSrcs.tcl

open_bd_design $BdFolder/top/top.bd
write_bd_tcl -force $BdFolder/top.tcl
