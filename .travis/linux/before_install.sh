#!/bin/bash

sudo add-apt-repository --yes ppa:ubuntu-sdk-team/ppa
sudo add-apt-repository --yes ppa:ubuntu-toolchain-r/test
sudo apt-get update -qq
if [ "$BUILD_TYPE" = "coverage" ]; then 
  #sudo -H pip install --upgrade pip
  #sudo -H pip install --user cpp-coveralls
  #sudo pip install --upgrade pip
  #sudo pip install --user cpp-coveralls
  sudo apt-get install -y ruby-full rubygems lcov gdb
  gem install lcoveralls
fi