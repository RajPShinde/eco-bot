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
 *  @file    pathPlanner.cpp
 *  @author  Raj Shinde
 *  @author  Prasheel Renkuntla
 *  @date    12/02/2019
 *  @version 2.0
 *  @brief   Final Project - ecobot (A trash Collecting Robot)
 *  @section Implementation file for path planning through A star plugin.
 */

#include <stdio.h>
#include <set>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <ros/console.h>
#include <vector>
#include <map>
#include <limits>
#include <pathPlanner.hpp>
#include <pluginlib/class_loader.h>
#include <pluginlib/class_list_macros.h>

//register this planner as a BaseGlobalPlanner plugin
PLUGINLIB_EXPORT_CLASS(astar_plugin::AStarPlanner, nav_core::BaseGlobalPlanner)

namespace astar_plugin
{
  AStarPlanner::AStarPlanner() {
  }

  AStarPlanner::AStarPlanner(ros::NodeHandle &nh) {
    ROSNodeHandle = nh;
  }
 
  AStarPlanner::AStarPlanner(std::string name,
                             costmap_2d::Costmap2DROS *costmap_ros) {
   initialize(name, costmap_ros);
  }

  void AStarPlanner::initialize(std::string name,
                                costmap_2d::Costmap2DROS *costmap_ros) {
}

bool AStarPlanner::makePlan(const geometry_msgs::PoseStamped &start,
                            const geometry_msgs::PoseStamped &goal,
                            std::vector<geometry_msgs::PoseStamped> &plan) {
 return false;
}

void AStarPlanner::convertToMapCoordinates(float &x, float &y) {
}

int AStarPlanner::getCellIndex(float x, float y) {
  return 1;
}

void AStarPlanner::getCellCoordinates(int index, float &x, float &y) {
}

bool AStarPlanner::isCoordinateInBounds(float x, float y) {
  return false;
}

std::vector<int> AStarPlanner::runAStar(int startCell,
                                              int goalCell) {
  return 1;
}

std::vector<int> AStarPlanner::findPath(int startCell, 
                                        int goalCell, 
                                        std::vector<float> g_score) {
  return 1;
}


std::vector<int> AStarPlanner::constructPath(int startCell,
                                             int goalCell,
                                             std::vector<float> g_score) {
  return 1;
}

void AStarPlanner::addNeighborGridSquareToOpenList(
	std::set<std::vector<std::pair<int, float>>> &openSquaresList,
    int neighborGridSquare, 
    int goalGridSquare, 
    std::vector<float> g_score) {
}

std::vector<int> AStarPlanner::findFreeNeighborCell(int cell) {
  return 1;
}

bool AStarPlanner::isStartAndGoalValid(int startGridSquare, int goalGridSquare)
{
  return false;
}

float AStarPlanner::getMoveToCellCost(int i1, int j1, int i2, int j2)
{
  return 10.0;
}

float AStarPlanner::getMoveToCellCost(int cellIndex1, int cellIndex2) {
  return 10.0;
}

float AStarPlanner::calculateHCellScore(int cellIndex, int cellSquare) {
  return 10.0;
}

int AStarPlanner::calculateCellIndex(int i, int j) {
  return 1;
}

int AStarPlanner::getCellRowIndex(int index) {
  return 1;
}

int AStarPlanner::getCellColIndex(int index) {
  return 1;
}

bool AStarPlanner::isCellFree(int i, int j) {
  return false;
}

bool AStarPlanner::isCellFree(int cellIndex) {
  return false;
}

};

bool operator<(std::vector<std::pair<int, float>> const &c1,
               std::vector<std::pair<int, float>> const &c2) { 
  //  return c1.fCost < c2.fCost; 
  return false;
}
