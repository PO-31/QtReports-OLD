#!/bin/bash

packages_list='qt5-default qttools5-dev-tools'
if [ "$BUILD_TYPE" = "doxygen" ]; then 
  packages_list+=' doxygen'
fi

echo $packages_list

# sudo apt-get update
sudo apt-get install -y $packages_list
