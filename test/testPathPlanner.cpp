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
 *  @file    testPartPlanner.cpp
 *  @author  Raj Shinde
 *  @author  Prasheel Renkuntla
 *  @date    12/09/2019
 *  @version 3.0 
 *  @brief   Final Project - ecobot (A trash Collecting Robot)
 *  @section Test cases for pathPlanner Algorithm
 */

#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/Twist.h>
#include <gtest/gtest.h>

#include <cstdlib>
#include <memory>
#include <stdio.h>
#include <set>
#include <numeric>
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
#include <iterator>
#include <algorithm>
#include <string>
#include <ros/console.h>
#include <vector>
#include <sstream>
#include <map>
#include <limits>
#include "pathPlanner.hpp"
// #include "gridSquare.hpp"

#include <geometry_msgs/Point.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <tf/transform_listener.h>
#include <costmap_2d/costmap_2d_ros.h>

/**
 * @def TEST(TestPathPlanner, testNodeHandle)
 * @brief To check if the robot node is testPlanner
 */
TEST(TestPathPlanner, testNodeHandle) {
//  Create a test node handle
ros::NodeHandle nh;
astar_plugin::AStarPlanner testPP(nh);
//  current node name
std::string node_name = "/testPlanner";
//  Returns true when robot name is testPlanner
EXPECT_EQ(node_name, ros::this_node::getName());
}

/**
 * @def TEST(TestPathPlanner, testConversionToMap)
 * @brief To check if the coordinates convert to Map
 */
TEST(TestPathPlanner, testConversionToMap) {
//  Initialise test object
astar_plugin::AStarPlanner testPP;
testPP.originX = 0;
testPP.originY = 0;
float point = 10.0;
float& indCoordinate = point;
//  Convert to map coordinates
testPP.convertToMapCoordinates(indCoordinate, indCoordinate);
std::vector<float> testCoordinates {10.0, 10.0};
//  Should return true when testcoordinates are equal to 10, 10
EXPECT_EQ(testCoordinates, testPP.getMapCoordinates(indCoordinate, indCoordinate));
}

/**
 * @def TEST(TestPathPlanner, testCheckCellCoordinates)
 * @brief To check for the map coordinates from given coordinates
 */
TEST(TestPathPlanner, testCheckCellCoordinates) {
//  initialise test object
astar_plugin::AStarPlanner testPP;
testPP.originX = 0;
testPP.originY = 0;
float point = 10.0;
float& indCoordinate = point;
int index = 0;
testPP.width = 10;
testPP.resolution = 180.0;

//  fetch the cell coordinates using the index, and individual coordinates
testPP.getCellCoordinates(index, indCoordinate, indCoordinate);
std::vector<float> testCoordinates {0.0, 0.0};

//  Should return true when the testcoordinates are at origin
EXPECT_EQ(testCoordinates, testPP.getMapCoordinates(indCoordinate, indCoordinate));
}

/**
 * @def TEST(TestPathPlanner, testCoordinateBounds)
 * @brief To check if the coordinates are within boundary
 */
TEST(TestPathPlanner, testCoordinateBounds) {
astar_plugin::AStarPlanner testPP;
//  The testcoordinates should be out of boundary when map params not initialised.
EXPECT_FALSE(testPP.isCoordinateInBounds(10, 10));
}

/**
 * @def TEST(TestPathPlanner, testCellValuesIndex)
 * @brief To check if the cell is free at a given index
 */
TEST(TestPathPlanner, testCellValuesIndex) {
astar_plugin::AStarPlanner testPP;
testPP.width = 10;
testPP.height = 10;
testPP.mapSize = testPP.width * testPP.height;
//  create a test occupancy grid
testPP.occupancyGridMap = new bool[testPP.mapSize];
//  Should return false for origin.
EXPECT_FALSE(testPP.isCellFree(0));
}

/**
 * @def TEST(TestPathPlanner, testCellValues)
 * @brief To check if the cells are free at given X,Y.
 */
TEST(TestPathPlanner, testCellValues) {
astar_plugin::AStarPlanner testPP;
testPP.width = 10;
testPP.height = 10;
testPP.mapSize = testPP.width * testPP.height;
//  Create a test occupancy grid
testPP.occupancyGridMap = new bool[testPP.mapSize];
//  Should return false for origin.
EXPECT_FALSE(testPP.isCellFree(0, 0));
}

/**
 * @def TEST(TestPathPlanner, testCellIndexCalculation)
 * @brief To check the cell index value
 */
TEST(TestPathPlanner, testCellIndexCalculation) {
astar_plugin::AStarPlanner testPP;
int res = 0;
//  Should return 0 for origin when no map params
EXPECT_EQ(res, testPP.calculateCellIndex(0, 0));
}

/**
 * @def TEST(TestPathPlanner, testCellIndex)
 * @brief To check for the given cell index
 */
TEST(TestPathPlanner, testCellIndex) {
astar_plugin::AStarPlanner testPP;
int res = 0;
//  index should be zero for origin.
EXPECT_EQ(res, testPP.getCellIndex(0, 0));
}

/**
 * @def TEST(TestPathPlanner, testRowIndex) 
 * @brief To check for the cell row index
 */
TEST(TestPathPlanner, testRowIndex) {
astar_plugin::AStarPlanner testPP;
testPP.width = 10;
int res = 0;
//  Should return 0 for the origin index.
EXPECT_EQ(res, testPP.getCellRowIndex(0));
}

/**
 * @def TEST(TestPathPlanner, testColIndex)
 * @brief To check for the cell column index
 */
TEST(TestPathPlanner, testColIndex) {
astar_plugin::AStarPlanner testPP;
testPP.width = 10;
int res = 0;
//  Should return 0 for the cell column index
EXPECT_EQ(res, testPP.getCellColIndex(0));
}

/**
 * @def TEST(TestPathPlanner, testHValue)
 * @brief To check for the H Function value.
 */
TEST(TestPathPlanner, testHValue) {
astar_plugin::AStarPlanner testPP;
testPP.width = 10;
float resF= 0.0;
//  At origin the H Cell score is 0.
EXPECT_EQ(resF, testPP.calculateHCellScore(0, 0));
}

/**
 * @def TEST(TestPathPlanner, testMovingCost)
 * @brief To check for the moving cell cost from origin.
 */
TEST(TestPathPlanner, testMovingCost) {
astar_plugin::AStarPlanner testPP;
testPP.width = 10;
float infinity = std::numeric_limits<float>::infinity();
float resF = infinity;
//  Should be infinite for origin.
EXPECT_EQ(resF, testPP.getMoveToCellCost(0, 0));
}

/**
 * @def TEST(TestPathPlanner, testMovingCostIndividualDiagonal)
 * @brief To check for moving cost in diagonal direction
 */
TEST(TestPathPlanner, testMovingCostIndividualDiagonal) {
astar_plugin::AStarPlanner testPP;
float resF = 1.4;
//  Should return root 2 for diagonal movement
EXPECT_EQ(resF, testPP.getMoveToCellCost(1, 1, 2, 2));
}

/**
 * @def TEST(TestPathPlanner, testMovingCostIndividualStraight) 
 * @brief To check for moving cost in straight line
 */
TEST(TestPathPlanner, testMovingCostIndividualStraight) {
astar_plugin::AStarPlanner testPP;
float resF = 1;
//  Should return 1 for straight line motion
EXPECT_EQ(resF, testPP.getMoveToCellCost(1, 1, 0, 1));
}

/**
 * @def TEST(testPathPlanner, testNeighborCellNewPoint) 
 * @brief To check for free neighbor cells at an index
 */
TEST(testPathPlanner, testNeighborCellNewPoint) {
astar_plugin::AStarPlanner testPP;
std::vector<int> resCells = {0};
testPP.width = 10;
//  Given index 10, without map the free neighbor cells are 0.
EXPECT_EQ(resCells,(testPP.findFreeNeighborCell(10)));
}

/**
 * @def TEST(testPathPlanner, testNeighborCell) 
 * @brief To check for free neighbour cells at origin
 */
TEST(testPathPlanner, testNeighborCell) {
astar_plugin::AStarPlanner testPP;
std::vector<int> resCells = {0};
testPP.width = 10;
//  Without map, the free neighbor cells are 0.
EXPECT_EQ(resCells,(testPP.findFreeNeighborCell(0)));
}

/**
 * @def TEST(TestPathPlanner, testConstructPath)
 * @brief To check the constructed path
 */
TEST(TestPathPlanner, testConstructPath) {
astar_plugin::AStarPlanner testPP;
float infinity = std::numeric_limits<float>::infinity();
std::vector<float> g_test = {infinity};
std::vector<int> resF = {0};
//  without a given map, it should return 0.
EXPECT_EQ(resF, testPP.constructPath(0, 0, g_test));
}

/**
 * @def TEST(TestPathPlanner, testFindPath) 
 * @brief To check if found path is correct at zero g_score
 */
TEST(TestPathPlanner, testFindPath) {
astar_plugin::AStarPlanner testPP;

testPP.value = 0;
float infinity = std::numeric_limits<float>::infinity();
std::vector<float> g_test = {0};
std::vector<int> resF = {0};
//  Should return 0 for origin.
EXPECT_EQ(resF, testPP.findPath(0, 0, g_test));
}

/**
 * @def TEST(TestPathPlanner, testFindPathNew)
 * @brief To check if found path is correct at infinite g_score
 */
TEST(TestPathPlanner, testFindPathNew) {
astar_plugin::AStarPlanner testPP;

testPP.value = 0;
float infinity = std::numeric_limits<float>::infinity();
std::vector<float> g_test = {infinity};
std::vector<int> resF = {0};
testPP.width = 10;
//  Should return 0 for origin.
EXPECT_EQ(resF, testPP.findPath(0, 0, g_test));
}

/**
 * @def TEST(TestPathPlanner, testFindPathNewFilled)
 * @brief To check if found path is correct
 */
TEST(TestPathPlanner, testFindPathNewFilled) {
astar_plugin::AStarPlanner testPP;

testPP.value = 0;
float infinity = std::numeric_limits<float>::infinity();
std::vector<float> g_test = {infinity};
std::vector<int> resF = {10};
testPP.width = 10;
//  Should return 10 for the given coordinate
EXPECT_EQ(resF, testPP.findPath(10, 10, g_test));
}

/**
 * @def TEST(TestPathPlanner, testFindPathNewExtreme)
 * @brief To check if the robot is able to twist on given topic
 */
TEST(TestPathPlanner, testFindPathNewExtreme) {
astar_plugin::AStarPlanner testPP;
//GridSquare gs;
testPP.value = 0;
float infinity = std::numeric_limits<float>::infinity();
std::vector<float> g_test = {infinity};
std::vector<int> resF = {1000};
testPP.width = 1;
//  Should return 1000 for extreme coordinates
EXPECT_EQ(resF, testPP.findPath(1000, 1000, g_test));
}

/**
 * @def TEST(TestPathPlanner, testRunAStar) 
 * @brief To check if A Star runs correctly.
 */
TEST(TestPathPlanner, testRunAStar) {
astar_plugin::AStarPlanner testPP;
//GridSquare gs;
testPP.value = 0;
float infinity = std::numeric_limits<float>::infinity();
std::vector<float> g_test = {infinity};
std::vector<int> resF = {0};
testPP.width = 10;
testPP.height = 10;
testPP.mapSize = testPP.width * testPP.height;
testPP.occupancyGridMap = new bool[testPP.mapSize];
//  Given the map, the result should be 0.
EXPECT_EQ(resF, testPP.runAStar(0, 0));
}

/**
 * @def TEST(TestPathPlanner, testStartGoalValidationFirst)
 * @brief To check if start and end goal are within map
 */
TEST(TestPathPlanner, testStartGoalValidationFirst) {
astar_plugin::AStarPlanner testPP;
testPP.width = 10;
testPP.height = 10;
testPP.mapSize = testPP.width * testPP.height;
//  Create a test occupancy grid
testPP.occupancyGridMap = new bool[testPP.mapSize];
//  Should return false for origin
EXPECT_FALSE(testPP.isStartAndGoalValid(0, 0));
}

/**
 * @def TEST(TestPathPlanner, testStartGoalValidationSecond) 
 * @brief To check if start and end goal are within map.
 */
TEST(TestPathPlanner, testStartGoalValidationSecond) {
astar_plugin::AStarPlanner testPP;
testPP.width = 10;
testPP.height = 10;
testPP.mapSize = testPP.width * testPP.height;
//  Create a test occupancy grid
testPP.occupancyGridMap = new bool[testPP.mapSize];
//  Should return false for the 1, 1
EXPECT_FALSE(testPP.isStartAndGoalValid(1, 1));
}

/**
 * @def TEST(TestPathPlanner, testFindPathThorough) 
 * @brief To check if found path is best path
 */
TEST(TestPathPlanner, testFindPathThorough) {
astar_plugin::AStarPlanner testPP;
testPP.width = 5.0;
testPP.height = 5.0;
float infinity = std::numeric_limits< float >::infinity();
int startCell = 1;
int endCell = 23;
int mapSize = testPP.width*testPP.height;
//  Create a test occupancy grid
testPP.occupancyGridMap = new bool[mapSize];
for (unsigned int iy = 0; iy < testPP.height; iy++) {
  for (unsigned int ix = 0; ix < testPP.width; ix++) {
   int cost = 0;
   if (cost == 0) {
      testPP.occupancyGridMap[iy*testPP.width+ix] = true;
      }
   }
}
//  Fill the occupancy grid
std::vector<float> g_score;
g_score.assign(mapSize, infinity);
int ints[] = {1, 0, 23};
std::vector <int> test (ints, ints+sizeof(ints)/sizeof(int));
std::vector<int> bpath;
//  Call the find path and get the best path
bpath =  testPP.findPath(startCell, endCell, g_score);
//  Should be 1, 0, 23 for the given path.
EXPECT_EQ(test, bpath);
//  Delete the map.
delete[] testPP.occupancyGridMap;
}

/**
 * @def TEST(TestPathPlanner, testFindFreeNeighborCell)
 * @brief To check for the free neighbor cells for a map
 */
TEST(TestPathPlanner, testFindFreeNeighborCell) {
astar_plugin::AStarPlanner testPP;
testPP.width = 3.0;
testPP.height = 3.0;
int id = 4;
int mapSize = testPP.width*testPP.height;
testPP.occupancyGridMap = new bool[mapSize];
//  Fill the occupancy grid
for (unsigned int iy = 0; iy < testPP.height; iy++) {
  for (unsigned int ix = 0; ix < testPP.width; ix++) {
   int cost = 0;

    if (cost == 0) {
      testPP.occupancyGridMap[iy*testPP.width+ix] = true;
     }
   }
}
int ints[] = {0, 0, 1, 2, 3, 5, 6, 7, 8};
std::vector <int> test (ints, ints+sizeof(ints)/sizeof(int));
std::vector <int> nay;
nay =  testPP.findFreeNeighborCell(id);
//  For the given id, the test should give us free cells.
EXPECT_EQ(test, nay);
//  Delete the map.
delete[] testPP.occupancyGridMap;
}

/**
 * @def TEST(TestPathPlanner, testAddNeighborsToOpenList)
 * @brief To check if open list is getting filled.
 */
TEST(TestPathPlanner, testAddNeighborsToOpenList) {
astar_plugin::AStarPlanner testPP;
int neighborCell = 1;
int goalCell = 3;
testPP.width = 5.0;
testPP.height = 5.0;
int mapSize = testPP.width*testPP.height;
float infinity = std::numeric_limits< float >::infinity();
std::vector<float> g_score;
//  fill the g_score vector with inf
g_score.assign(mapSize, infinity);
std::set<GridSquare> OPL;
//  Should return true if empty.
EXPECT_EQ(true, OPL.empty());
//  Should return the OPL list for the given neighbor cells.
testPP.addNeighborCellToOpenList(OPL, neighborCell, goalCell, g_score);
//  Should return false as the list is filled.
EXPECT_EQ(false, OPL.empty());
}

/**
 * @def TEST(TestPathPlanner, testIsStartGoalValid) 
 * @brief To check for the start and goal in boundary
 */
TEST(TestPathPlanner, testIsStartGoalValid) {
astar_plugin::AStarPlanner testPP;
    int start1 = 10;
    int goal1 = 10;

    int start2 = 90;
    int goal2 = 91;

    int start3 = 90;
    int goal3 = 10;

    int start4 = 10;
    int goal4 = 90;

    int start5 = 10;
    int goal5 = 11;

    testPP.width = 5;
    testPP.height = 5;
    int mapSize = testPP.width*testPP.height;
    testPP.occupancyGridMap = new bool[mapSize];
    //  Fill the occupancy grid
    for (unsigned int iy = 0; iy < testPP.height; iy++) {
      for (unsigned int ix = 0; ix < testPP.width; ix++) {
       int cost = 0;

        if (cost == 0) {
          testPP.occupancyGridMap[iy*testPP.width+ix] = true;
         }
       }
    }
    //  Check for the given outer boundary conditions.
    EXPECT_EQ(false, testPP.isStartAndGoalValid(start1, goal1));
    EXPECT_EQ(false, testPP.isStartAndGoalValid(start2, goal2));
    EXPECT_EQ(false, testPP.isStartAndGoalValid(start3, goal3));
    EXPECT_EQ(false, testPP.isStartAndGoalValid(start4, goal4));
    EXPECT_EQ(true , testPP.isStartAndGoalValid(start5, goal5));
    //  Delete the map.
    delete[] testPP.occupancyGridMap;
}

// Currently under Development
// TEST(TestPathPlanner, testAStarCostMap) {
// bool initialized = true;
// std::string name = "AStarPlanner";
// tf::TransformListener tf_(ros::Duration(10));
// auto costmap_ros_ = new costmap_2d::Costmap2DROS("my_costmap", tf_);

// astar_plugin::AStarPlanner testPP;
// testPP.initialize(name, costmap_ros_);

// // EXPECT_EQ(true, initialized);
// }
// TEST(TestPathPlanner, testMakePlanFalse) {
// bool initialized = false;
// // geometry_msgs::PoseStamped pose_msg;
// geometry_msgs::PoseStamped msgPose1;
// ros::Time start = ros::Time::now();
// msgPose1.header.stamp = start;
// msgPose1.header.frame_id = "map";
// msgPose1.pose.position.x = 0;
// msgPose1.pose.position.y = 0;
// msgPose1.pose.position.z = 0.25;
// tf::Transform transform;
// transform.setOrigin(tf::Vector3(0.0, 0.0, 0.0));
// tf::Quaternion quaternion1;
// quaternion1.setRPY(0.5, 0.9, 1.90);
// //auto quaternion = tf.transformations.quaternion_from_euler(0, 0, 0);
// msgPose1.pose.orientation.x = quaternion1[0];
// msgPose1.pose.orientation.y = quaternion1[1];
// msgPose1.pose.orientation.z = quaternion1[2];
// msgPose1.pose.orientation.w = quaternion1[3];
// geometry_msgs::PoseStamped& poseStart = msgPose1;

// geometry_msgs::PoseStamped msgPose2;
// ros::Time goal = ros::Time::now();
// msgPose2.header.stamp = goal;
// msgPose2.header.frame_id = "map";
// msgPose2.pose.position.x = 0;
// msgPose2.pose.position.y = 0;
// msgPose2.pose.position.z = 0.25;
// transform.setOrigin(tf::Vector3(0.0, 0.0, 0.0));
// tf::Quaternion quaternion2;
// quaternion2.setRPY(1.5, 0.0, 1.0);
// //auto quaternion = tf.transformations.quaternion_from_euler(0, 0, 0);
// msgPose2.pose.orientation.x = quaternion2[0];
// msgPose2.pose.orientation.y = quaternion2[1];
// msgPose2.pose.orientation.z = quaternion2[2];
// msgPose2.pose.orientation.w = quaternion2[3];
// geometry_msgs::PoseStamped& poseGoal = msgPose2;

// std::vector<geometry_msgs::PoseStamped> vecPlan = {poseStart, poseGoal};
// std::vector<geometry_msgs::PoseStamped>& plan = vecPlan;
//  tf::TransformListener tf_(ros::Duration(0.01));
// auto costmap_ros_ = new costmap_2d::Costmap2DROS("my_costmap", tf_);
// astar_plugin::AStarPlanner testPP;
// testPP.initialize("testPlanner", costmap_ros_);
// EXPECT_FALSE(testPP.makePlan(poseStart, poseGoal, vecPlan));
// }

// geometry_msgs::Point point(1, 2, 3);
// geometry_msgs::Pose pose(point, geometry_msgs::Quaternion(4,5,6,7));

// geometry_msgs::PoseStamped& poseStart = msgPose1;

// const geometry_msgs::PoseStamped msgPose2;
// ros::Time goal = ros::Time::now();
// msgPose2.header.stamp = goal;
// msgPose2.header.frame_id = "map";
// msgPose2.pose.position.x = 0;
// msgPose2.pose.position.y = 0;
// msgPose2.pose.position.z = 0.25;
// quaternion = tf.transformations.quaternion_from_euler(0, 0, 0);
// msgPose2.pose.orientation.x = quaternion[0];
// msgPose2.pose.orientation.y = quaternion[1];
// msgPose2.pose.orientation.z = quaternion[2];
// msgPose2.pose.orientation.w = quaternion[3];

// geometry_msgs::PoseStamped& poseGoal = msgPose2;
//