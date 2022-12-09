cmake_minimum_required(VERSION 3.18)
project(SimASM)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(SimASM src/main.cpp src/FileParsing.hpp src/FileParsing.cpp)
