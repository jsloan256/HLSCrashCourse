set CurrentProjectDirectory [get_property DIRECTORY [current_project] ]
cd $CurrentProjectDirectory

write_hw_platform -fixed -include_bit -force -file $CurrentProjectDirectory/../Export/top_wrapper.xsa
