#!/bin/sh

BUILD_DIR="build"
GENERATOR=""

if [[ $OSTYPE == "darwin"* ]]; then
  #Mac OSX
  GENERATOR="-G Xcode"
fi

cmake $GENERATOR -S . -B $BUILD_DIR&&cmake --build $BUILD_DIR --config Release 

