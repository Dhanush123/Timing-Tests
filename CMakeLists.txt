cmake_minimum_required(VERSION 3.6)
project(Schedule_2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(SOURCE_FILES ParsingWithoutDupChecking.cpp)
add_executable(Schedule_2 ${SOURCE_FILES})