#!/bin/bash

cd ../HCCLinux
petalinux-build --sdk
petalinux-build --sdk

echo "======================================================================="
echo "======================================================================="
echo "When prompted, enter './sdk' as the target director for the SDK folder."
echo "======================================================================="
echo "======================================================================="

cd images/linux
./sdk.sh

cd ../../../Scripts
