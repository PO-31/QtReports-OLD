#!/bin/bash

packages=''
if [ "$BUILD_TYPE" = "doxygen" ]; then 
  packages+=' doxygen'
else
  packages+=' qt5-default qttools5-dev-tools'
fi

# sudo apt-get update
sudo apt-get install -y $add_packages
