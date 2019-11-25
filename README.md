# Object Collector Robot
[![Build Status](https://travis-ci.org/Prasheel24/Object-Collector-Robot.svg?branch=master)](https://travis-ci.org/Prasheel24/Object-Collector-Robot)
[![Coverage Status](https://coveralls.io/repos/github/Prasheel24/Object-Collector-Robot/badge.svg?branch=master&service=github)](https://coveralls.io/github/Prasheel24/Object-Collector-Robot?branch=master)
[![License BSD 3-Clause](https://img.shields.io/badge/License-BSD%203--Clause-blue.svg)](https://github.com/Prasheel24/Object-Collector-Robot/blob/master/LICENSE)
---

## Authors

* **Raj Prakash Shinde** [GitHub](https://github.com/RajPShinde)
<br>I am a Masters in Robotics Engineering student at the University of Maryland, College Park. My primary area of interest are Legged Robotics and Automation. 
* **Prasheel Renkuntla** [GitHub](https://github.com/Prasheel24)
<br>I am a Master's in Robotics Engineering student at the University of Maryland, College Park. My primary area of interest is in Vision integrated Robot Systems.

## Overview
This is an Object Collector Robot ROS Package developed for ACME Robotics to demonstrate the functionality of their product.

## Sprint Planning and Discussion
Sprint- https://docs.google.com/document/d/1_uG7fMXPrtZlpRLsgD74NdLRX3DKDXxCicppZWBDNvQ

## Agile Iterative Process Log
Log- https://docs.google.com/spreadsheets/d/1DkxCx4_GxvRXjRTTrmgZvdOQ4z0DMrpGEavg439tQak

## Dependencies
1. Ubuntu 16.04
2. C++ 11/14/17
3. ROS Kinetic
4. Turtlebot stack
<br> Install by running following command
```

sudo apt-get install ros-kinetic-turtlebot-gazebo ros-kinetic-turtlebot-apps ros-kinetic-turtlebot-rviz-launchers
```

## Build
Steps to build
```
mkdir -p ~/catkin_ws/src
cd ~/catkin_ws/
catkin_make
source devel/setup.bash
cd src/
git clone https://github.com/Prasheel24/Object-Collector-Robot
cd ~/catkin_ws/
catkin_make
```

## References
* http://wiki.ros.org/

## Disclaimer
This software is released under the BSD 3-Clause license.