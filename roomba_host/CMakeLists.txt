cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

find_package(gazebo REQUIRED)
include_directories(${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})
list(APPEND CMAKE_CXX_FLAGS "${GAZEBO_CXX_FLAGS}")

add_library(roombamodel SHARED roombamodel.cc)
target_link_libraries(roombamodel
  ${GAZEBO_LIBRARIES})

add_library(roombasim SHARED roombasim.cc)
target_link_libraries(roombasim ${GAZEBO_LIBRARIES} ${Boost_LIBRARIES})

add_library(roombacircle SHARED roombacircle.cc)
target_link_libraries(roombacircle ${GAZEBO_LIBRARIES})
