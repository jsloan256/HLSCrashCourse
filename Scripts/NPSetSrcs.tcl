set PartName "xc7z007sclg400-1"
#set BoardName "digilentinc.com:cora-z7-07s:part0:1.0"

# The following two variables are only used in project-mode
set Design HLSCrashCourse
set ProjectDir ../Vivado/
set NumThreads 24

# Assemble the Design Source Files (all paths are relative *except* for ScriptsAbsolute
set ScriptsAbsolute [pwd]
set Root ".."
#set HdlFolder [list $Root/Sources/HDL/]
set BdFolder [list $Root/Sources/BlockDiagram]
set WrapFolder [list $Root/Sources/BlockDiagram/top/hdl]
#set XciFolders [glob $Root/Sources/IP/* -type f]
#set SimFolder [list $Root/Sources/Simulation/]
set ConstrFolder [list $Root/Sources/Constraints]
set IpRepos [list $Root/Sources/HLS/]
set ExportFolder $Root/Export

# Block Diagram Files
#set BdRestoreRelative {top_bd.tcl.relative}
#set MPSoCForZCU {ZcuZynq.tcl}
#set BdRestoreForZCU {top_bd.tcl.relative.zynq}

# Top-level Modules
set Top top_wrapper
set TopSim top_wrapper

# Folders for Results
#set OutputFolder $Root/np
#set FullBaselineFolder $OutputFolder/FullBaseline
#set ClksBaselineFolder $OutputFolder/ClksBaseline

# Create Results Folders
#file mkdir $OutputFolder
#file mkdir $FullBaselineFolder
#file mkdir $ClksBaselineFolder
#file mkdir $ExportFolder
