cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME "swapping_algorithms_lib")

project (swapping_algorithms)
set(CMAKE_BUILD_TYPE Release)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(${PROJECT_NAME} SHARED src/fifo.cc
                                   src/second_chance.cc
                                   src/optimal.cc
                                   src/mru.cc
                                   src/nur.cc
                                   src/runner.cc)
