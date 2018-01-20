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

add_library(target1 SHARED target1.cc)
target_link_libraries(target1 ${GAZEBO_LIBRARIES})

add_library(target2 SHARED target2.cc)
target_link_libraries(target2 ${GAZEBO_LIBRARIES})

add_library(target3 SHARED target3.cc)
target_link_libraries(target3 ${GAZEBO_LIBRARIES})

add_library(target4 SHARED target4.cc)
target_link_libraries(target4 ${GAZEBO_LIBRARIES})

add_library(target5 SHARED target5.cc)
target_link_libraries(target5 ${GAZEBO_LIBRARIES})

add_library(target6 SHARED target6.cc)
target_link_libraries(target6 ${GAZEBO_LIBRARIES})

add_library(target7 SHARED target7.cc)
target_link_libraries(target7 ${GAZEBO_LIBRARIES})

add_library(target8 SHARED target8.cc)
target_link_libraries(target8 ${GAZEBO_LIBRARIES})

add_library(target9 SHARED target9.cc)
target_link_libraries(target9 ${GAZEBO_LIBRARIES})

add_library(target10 SHARED target10.cc)
target_link_libraries(target10 ${GAZEBO_LIBRARIES})






