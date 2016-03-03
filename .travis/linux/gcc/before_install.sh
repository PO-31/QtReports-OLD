#!/bin/bash

sudo add-apt-repository --yes ppa:ubuntu-sdk-team/ppa
sudo add-apt-repository --yes ppa:ubuntu-toolchain-r/test
sudo apt-get update -qq
sudo apt-get install gcc-4.8 g++-4.8 qt5-default
sudo -H pip install --upgrade pip
sudo -H pip install --user cpp-coveralls