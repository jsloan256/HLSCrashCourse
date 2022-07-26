set filename "top_bd.tcl"

# Slurp the file in
set f [open $BDFilename]
set data [read $f]
close $f

#puts $data
set lines [split $data \n]
#puts $lines
foreach line $lines {
  set match [regexp "^  set origin_dir.*" $line]
#  puts $match
  if {$match} {
    set origin $line
  }
}

puts $origin
set mapping [list $origin {  set origin_dir ../../.}]

# Apply the mapping
set data [string map $mapping $data]

# Write back with a separate open
set f [open $BDFilename.relative w]
puts -nonewline $f $data
close $f
