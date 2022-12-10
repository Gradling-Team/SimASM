cmake_minimum_required(VERSION 3.24)
project(SimASM)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include_directories(src/SyntaxSubClasses)

add_executable(SimASM
        src/FileParsing.cpp
        src/FileParsing.hpp
        src/main.cpp
        src/SyntaxChecker.cpp
        src/SyntaxChecker.hpp)
