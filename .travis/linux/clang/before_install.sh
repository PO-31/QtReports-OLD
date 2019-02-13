#!/bin/bash

sudo apt-add-repository --yes "deb http://apt.llvm.org/xenial/ llvm-toolchain-xenial-7 main"
sudo apt-get update -qq
sudo apt-get -f install -y clang-7 qt5-default qttools5-dev-tools

update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-3.8 100
update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-7 1000
update-alternatives --install /usr/bin/clang++ clang /usr/bin/clang-3.8 100
update-alternatives --install /usr/bin/clang clang /usr/bin/clang-3.8 100
update-alternatives --install /usr/bin/clang clang /usr/bin/clang-7 1000
update-alternatives --config clang
update-alternatives --config clang++
