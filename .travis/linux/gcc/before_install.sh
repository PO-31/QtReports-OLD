#!/bin/bash

sudo add-apt-repository --yes ppa:ubuntu-sdk-team/ppa
sudo add-apt-repository --yes ppa:ubuntu-toolchain-r/test
sudo apt-get update -qq
sudo apt-get install gcc-4.8 g++-4.8 qt5-default
pip install --user cpp-coveralls
export USING_QT_MKSPEC="linux-g++-64"