cmake_minimum_required(VERSION 3.0.2)
project(ros_hologram)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  sensor_msgs
  std_msgs
  tf2_ros
  tf2_geometry_msgs
)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)
find_package(PCL 1.3 REQUIRED COMPONENTS)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES ROS_Hologram
 CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)
 
add_executable(pointcloud_filter src/pointcloud_filter.cpp)
target_link_libraries(pointcloud_filter ${catkin_LIBRARIES})
# add_dependencies(pointcloud_filter ros_hologram)
target_link_libraries(pointcloud_filter ${PCL_LIBRARIES})

add_executable(pointcloud_sub src/pointcloud_sub.cpp)
target_link_libraries(pointcloud_sub ${catkin_LIBRARIES})
target_link_libraries(pointcloud_sub ${PCL_LIBRARIES})