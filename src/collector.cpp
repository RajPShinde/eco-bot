/************************************************************************
BSD 3-Clause License

Copyright (c) 2019, Raj Shinde
Copyright (c) 2019, Prasheel Renkuntla
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *************************************************************************/

/**
 *  @copyright BSD 3-Clause License 
 *  @copyright Copyright © 2019 Raj Shinde, Prasheel Renkuntla
 *  @file    collector.cpp
 *  @author  Prasheel Renkuntla
 *  @author  Raj Shinde
 *  @date    12/09/2019
 *  @version 3.0
 *  @brief   Final Project - ecobot (A trash Collecting Robot)
 *  @section Implemention of collection task
 */

#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include "spawnCollect.hpp"
#include "randomizer.hpp"
#include "collector.hpp"

typedef actionlib::SimpleActionClient
<move_base_msgs::MoveBaseAction> MoveBaseClient;

Collector::Collector() {
}
Collector::~Collector() {
}

bool Collector::collector() {
  bool flag = true;
  double xo = 0;
  double yo = 0;
  Randomizer r;
  SpawnCollect s;
  double xr = r.randomizeX();
  double yr = r.randomizeY();
  s.spawn(xr, yr, 1);

  double xn = -7.0 + xr;
  double yn = -6.5 + yr;
  xn = r.xOffset(xo, xr, xn);
  yn = r.yOffset(yo, yr, yn);

  // tell the action client  to spin a thread
  MoveBaseClient ac("move_base", true);

  // wait for action server
  while (!ac.waitForServer(ros::Duration(10.0))) {
    ROS_INFO_STREAM("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  // sending goal
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  goal.target_pose.pose.position.x = xn;
  goal.target_pose.pose.position.y = yn;
  goal.target_pose.pose.position.z = 0.0;
  goal.target_pose.pose.orientation.w = 1.0;

  ROS_INFO_STREAM("Sending goal");
  ac.sendGoal(goal);

  ac.waitForResult(ros::Duration(17 + 2.3 * abs(6.5 + yr)));
  
  //  if the robot reaches successfully then it will remove the trash
  if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
    ROS_INFO_STREAM("Hooray, Trash is collected!");
    s.collect(1);
  } else {
    ROS_INFO_STREAM("The base is in vicinity to the Object. Hence collected!");
    s.collect(1);
  }
return flag;
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "simple_navigation_goals");
  Collector trash;
  trash.collector();
  return 0;
}
