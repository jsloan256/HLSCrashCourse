set CurrentProjectDirectory [get_property DIRECTORY [current_project] ]
cd $CurrentProjectDirectory

remove_gui_custom_commands ExportBD
remove_gui_custom_commands ExportXSA

create_gui_custom_command -name ExportBD -tcl_file $CurrentProjectDirectory/../Scripts/ExportBD.tcl -description "Export Block Diagram to TCL for version control" -show_on_toolbar -toolbar_icon $CurrentProjectDirectory/../Scripts/ExportBDIcon.png

create_gui_custom_command -name ExportXSA -tcl_file $CurrentProjectDirectory/../Scripts/ExportXSA.tcl -description "Export XSA with bitstream" -show_on_toolbar -toolbar_icon $CurrentProjectDirectory/../Scripts/ExportXSAIcon.png

