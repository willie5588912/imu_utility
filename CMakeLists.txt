cmake_minimum_required(VERSION 2.8.3)
project(imu_utility)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  sensor_msgs
  std_msgs
)

generate_messages(DEPENDENCIES
	std_msgs
)

catkin_package(CATKIN_DEPENDS
	std_msgs
	roscpp
)

include_directories(
  	${catkin_INCLUDE_DIRS}
)

add_executable(ira_imu src/ira_imu.cpp)
target_link_libraries(ira_imu ${catkin_LIBRARIES})

