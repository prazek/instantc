#!/usr/bin/env bash
mkdir antlr-build
cd antlr-build
cmake ../antlr4/runtime/Cpp -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=$PWD
make -j16 install
