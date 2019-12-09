#[[
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
]]
cmake_minimum_required(VERSION 3.2.1)
project(ecobot)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 14)

find_package(catkin REQUIRED COMPONENTS 
  nav_core 
  move_base_msgs
  base_local_planner
  roscpp
  std_msgs
  tf
  rostest
  roscpp
  rospy
  message_generation)

###################################
## catkin specific configuration ##
###################################
catkin_package(
  INCLUDE_DIRS include
#  LIBRARIES cleaner_robot
   CATKIN_DEPENDS nav_core roscpp std_msgs
#  DEPENDS system_lib
)

## To run tests, add dependencies for gtest and rostest
if(CATKIN_ENABLE_TESTING)
  find_package(rostest REQUIRED)
  ##find_package(gtest)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 --coverage")

  catkin_add_gtest(testGrid test/testGridSquare.cpp src/gridSquare.cpp)
  target_link_libraries(testGrid ${catkin_LIBRARIES})

  catkin_add_gtest(testcollect test/testRandomizer.cpp test/testSpawnCollect.cpp src/randomizer.cpp src/spawnCollect.cpp)
  target_link_libraries(testcollect ${catkin_LIBRARIES})

  add_rostest_gtest(testPlanner launch/testPathPlanner.launch test/main.cpp test/testPathPlanner.cpp src/gridSquare.cpp src/pathPlanner.cpp)
  target_link_libraries(testPlanner ${catkin_LIBRARIES})
  add_dependencies(testPlanner pathPlanner ${catkin_EXPORTED_TARGETS})

  add_rostest_gtest(testNavigator launch/testNavigator.launch test/testNavigateRobot.cpp src/navigateRobot.cpp)
  target_link_libraries(testNavigator ${catkin_LIBRARIES})
  add_dependencies(testNavigator astar_move ${catkin_EXPORTED_TARGETS})
endif()

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations

include_directories(include ${catkin_INCLUDE_DIRS})

add_library(pathPlanner src/gridSquare.cpp src/pathPlanner.cpp)

add_executable(trash src/randomizer.cpp src/spawnCollect.cpp src/collector.cpp)
target_link_libraries(trash ${catkin_LIBRARIES})

add_executable(astar_move src/main.cpp src/navigateRobot.cpp)
add_dependencies(astar_move ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(astar_move ${catkin_LIBRARIES})

