#!/usr/bin/env bash
pushd Tests
git clone https://github.com/google/googletest.git
popd

pushd thirdparty
git clone https://github.com/antlr/antlr4.git
popd