#!/usr/bin/env bash

./get_dependencies.sh
#stupid script in order to use stupid makefile
mkdir build
cd build
cmake ../ -DCMAKE_RUNTIME_OUTPUT_DIRECTORY=$PWD/../
cd ..
cmake --build build
