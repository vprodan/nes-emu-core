cmake_minimum_required(VERSION 3.15)
project(NesEmulationCore)

set(CMAKE_C_COMPILER /usr/bin/cpp)
set(CMAKE_CXX_COMPILER /usr/bin/c++)

set(CMAKE_CXX_STANDARD 23)

include_directories(${CMAKE_SOURCE_DIR}/src)
add_executable(NesEmulationCore ${CMAKE_SOURCE_DIR}/src/main.cpp)