#!/bin/bash

sudo add-apt-repository --yes ppa:ubuntu-sdk-team/ppa
sudo add-apt-repository --yes ppa:ubuntu-toolchain-r/test
sudo apt-add-repository --yes ppa:beineri/opt-qt551
sudo apt-get update -qq
sudo apt-get -f install clang qt-latest
sudo -H pip install --upgrade pip
sudo -H pip install --user cpp-coveralls