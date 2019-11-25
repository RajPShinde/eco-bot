cmake_minimum_required(VERSION 3.2.1)
project(object_collector)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 14)

find_package(catkin REQUIRED COMPONENTS roscpp geometry_msgs sensor_msgs)

## Generate messages in the 'msg' folder
# add_message_files(
#   FILES
#   Message1.msg
#   Message2.msg
# )

## Generate services in the 'srv' folder
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
# generate_messages(
#   DEPENDENCIES
#   std_msgs
# )

###################################
## catkin specific configuration ##
###################################
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES cleaner_robot
#  CATKIN_DEPENDS genmsg geometry_msgs roscpp sensor_msgs std_msgs
#  DEPENDS system_lib
)

## To run tests, add dependencies for gtest and rostest
##if(CATKIN_ENABLE_TESTING)
##find_package(rostest REQUIRED)
##  add_rostest_gtest(testCleaner test/testCleanerRun.launch test/main.cpp test/testCleaner.cpp)
##  target_link_libraries(testCleaner ${catkin_LIBRARIES})
##  add_dependencies(tester cleanerBot beginner_tutorials_generate_messages_cpp ${catkin_EXPORTED_TARGETS})
##endif()


###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(include ${catkin_INCLUDE_DIRS})

##add_executable(objCollector src/main.cpp)
##target_link_libraries(objCollector ${catkin_LIBRARIES})

