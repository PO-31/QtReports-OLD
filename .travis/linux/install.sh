#!/bin/bash

export DISPLAY=:99.0
cat /etc/init.d/xvfb
sh -e /etc/init.d/xvfb start
sleep 3 # give xvfb some time to start