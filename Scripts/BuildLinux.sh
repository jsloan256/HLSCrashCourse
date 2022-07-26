#!/bin/bash

# petalinux 2020.2 settings be be sourced before running this script

cd ..
petalinux-create --type project --template zynq --name HCCLinux

cd HCCLinux
petalinux-config --get-hw-description=../Export --silentconfig

# Create simplegpio-example application using my source
petalinux-create -t apps --template c++ --name simplegpio-example --enable
# Copy application bitbake file
cp ../Sources/HLS/SimpleGpio/ExampleDriver/simplegpio-example.bb project-spec/meta-user/recipes-apps/simplegpio-example/.
# Copy main application code
cp ../Sources/HLS/SimpleGpio/ExampleDriver/src/* project-spec/meta-user/recipes-apps/simplegpio-example/files/.
# Copy header from HLS core to obtain interface structs
cp ../Sources/HLS/SimpleGpio/SimpleGpioIfStructs.h project-spec/meta-user/recipes-apps/simplegpio-example/files/.
# Copy HLS prebuilt drivers from compiled core project
cp ../Sources/HLS/SimpleGpio/SimpleGpioProject/Solution/impl/ip/drivers/SimpleGpioSyn_v1_01/src/*.c project-spec/meta-user/recipes-apps/simplegpio-example/files/.
cp ../Sources/HLS/SimpleGpio/SimpleGpioProject/Solution/impl/ip/drivers/SimpleGpioSyn_v1_01/src/*.h project-spec/meta-user/recipes-apps/simplegpio-example/files/.

# Update BSP meta layer
cp ../Sources/BSP/system-user.dtsi project-spec/meta-user/recipes-bsp/device-tree/files/.

# Update rootfs config
cp ../srcs/bsp/rootfs_config project-spec/configs/.

# Update kernel config
cp ../srcs/bsp/config project-spec/configs/.

petalinux-config -c kernel --silentconfig

# Build linux (re-run of petalinux-build is often required)
petalinux-build
petalinux-build

# Package linux for SD card
petalinux-package --boot --format BIN --fsbl images/linux/zynq_fsbl.elf --fpga images/linux/system.bit --u-boot --force
