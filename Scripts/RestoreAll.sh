#!/bin/bash

REQUIRED_VERSION="2022.1"

if ! vivado -version | grep -q $REQUIRED_VERSION; then
  echo "Wrong Vivado version in path. Should be $REQUIRED_VERSION"
  exit 1
fi

if ! vitis_hls -version | grep -q $REQUIRED_VERSION; then
  echo "Wrong Vitis HLS version in path. Should be $REQUIRED_VERSION"
  exit 1
fi

./RestoreHLS.sh
./RestoreVivadoProject.sh

rm -rf ../Export
