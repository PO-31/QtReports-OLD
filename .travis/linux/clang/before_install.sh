#!/bin/bash

sudo add-apt-repository --yes ppa:beineri/opt-qt-5.10.0-xenial
sudo apt-get update -qq
sudo apt-get -f install clang qt-latest
