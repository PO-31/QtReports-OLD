#!/bin/bash

sudo add-apt-repository --yes ppa:ubuntu-sdk-team/ppa
sudo add-apt-repository --yes ppa:ubuntu-toolchain-r/test
sudo apt-get update -qq
if [ "$BUILD_TYPE" = "coverage" ]; then sudo -H pip install --upgrade pip; fi
if [ "$BUILD_TYPE" = "coverage" ]; then sudo -H pip install --user cpp-coveralls; fi
if [ "$BUILD_TYPE" = "coverage" ]; then sudo pip install --upgrade pip; fi
if [ "$BUILD_TYPE" = "coverage" ]; then sudo pip install --user cpp-coveralls; fi
if [ "$BUILD_TYPE" = "coverage" ]; then sudo apt-get install -y ruby-full rubygems lcov; fi
if [ "$BUILD_TYPE" = "coverage" ]; then gem install coveralls-lcov; fi