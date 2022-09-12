#!/bin/bash

if [ -d "../HCCLinux/images/linux/sdk" ] 
then
  cd ..
  xsct Scripts/CreateWorkspace.tcl

  # Copy simplegpio-example source into the workspace
  cp Sources/HLS/SimpleGpio/ExampleDriver/src/* VitisWorkspace/simplegpio-example/src/.
  cp Sources/HLS/SimpleGpio/SimpleGpioTypes.h VitisWorkspace/simplegpio-example/src/.
  cp Sources/HLS/SimpleGpio/SimpleGpioProject/Solution/impl/ip/drivers/SimpleGpioSyn_v1_01/src/*.c VitisWorkspace/simplegpio-example/src/.
  cp Sources/HLS/SimpleGpio/SimpleGpioProject/Solution/impl/ip/drivers/SimpleGpioSyn_v1_01/src/*.h VitisWorkspace/simplegpio-example/src/.

  # Copy stream-example source into the workspace
  cp Sources/HLS/StreamControl/ExampleDriver/src/* VitisWorkspace/stream-example/src/.
  cp Sources/HLS/StreamControl/StreamControlTypes.h VitisWorkspace/stream-example/src/.
  cp Sources/HLS/StreamControl/StreamControlProject/Solution/impl/ip/drivers/StreamControlSyn_v1_01/src/*.c VitisWorkspace/stream-example/src/.
  cp Sources/HLS/StreamControl/StreamControlProject/Solution/impl/ip/drivers/StreamControlSyn_v1_01/src/*.h VitisWorkspace/stream-example/src/.

  cd Scripts

else
  echo "Error: ../HCCLinux/images/linux/sdk does not exist. Run ./CreateSDK.sh before running this script."
fi
