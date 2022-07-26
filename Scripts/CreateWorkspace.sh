#!/bin/bash

if [ -d "../HCCLinux/images/linux/sdk" ] 
then
  cd ..
  xsct Scripts/CreateWorkspace.tcl

  # Add copy source into the workspace
  cp Sources/HLS/SimpleGpio/ExampleDriver/src/* VitisWorkspace/simplegpio-example/src/.
  cp Sources/HLS/SimpleGpio/SimpleGpioIfStructs.h VitisWorkspace/simplegpio-example/src/.
  cp Sources/HLS/SimpleGpio/SimpleGpioProject/Solution/impl/ip/drivers/SimpleGpioSyn_v1_01/src/*.c VitisWorkspace/simplegpio-example/src/.
  cp Sources/HLS/SimpleGpio/SimpleGpioProject/Solution/impl/ip/drivers/SimpleGpioSyn_v1_01/src/*.h VitisWorkspace/simplegpio-example/src/.

  cd Scripts
else
  echo "Error: ../HCCLinux/images/linux/sdk does not exist. Run ./CreateSDK.sh before running this script."
fi
