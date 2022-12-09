cmake_minimum_required(VERSION 3.18)
project(SimASM)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(SimASM src/FileParsing.cpp src/FileParsing.h src/main.cpp)
