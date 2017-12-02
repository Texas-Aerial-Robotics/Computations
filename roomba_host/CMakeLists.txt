cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

find_package(gazebo REQUIRED)
include_directories(${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})
list(APPEND CMAKE_CXX_FLAGS "${GAZEBO_CXX_FLAGS}")


add_library(roombacircle SHARED roombacircle.cc)
target_link_libraries(roombacircle ${GAZEBO_LIBRARIES})

add_library(roombacircle2 SHARED roombacircle2.cc)
target_link_libraries(roombacircle2 ${GAZEBO_LIBRARIES})

add_library(roombacircle3 SHARED roombacircle3.cc)
target_link_libraries(roombacircle3 ${GAZEBO_LIBRARIES})

add_library(roombacircle4 SHARED roombacircle4.cc)
target_link_libraries(roombacircle4 ${GAZEBO_LIBRARIES})
