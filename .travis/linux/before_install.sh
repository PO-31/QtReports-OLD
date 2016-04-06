#!/bin/bash

sudo add-apt-repository --yes ppa:ubuntu-sdk-team/ppa
sudo add-apt-repository --yes ppa:ubuntu-toolchain-r/test
sudo apt-get update -qq
if [ "$BUILD_TYPE" = "coverage" ]; then 
  #sudo -H pip install --upgrade pip
  #sudo -H pip install --user cpp-coveralls
  #sudo pip install --upgrade pip
  #sudo pip install --user cpp-coveralls
  sudo apt-get install -y ruby1.9.1 rubygems1.9.1
  gem install lcoveralls
  sudo update-alternatives --install /usr/bin/ruby ruby /usr/bin/ruby1.9.1 100
  sudo update-alternatives --install /usr/bin/gem gem /usr/bin/gem1.9.1 100
fi