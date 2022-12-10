cmake_minimum_required(VERSION 3.18)
project(SimASM)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(SimASM src/main.cpp src/FileParsing.hpp src/FileParsing.cpp src/CPUSubClasses/StackRegisters.cpp src/CPUSubClasses/StackRegisters.hpp src/CPUSubClasses/Register.cpp src/CPUSubClasses/Register.hpp src/CPUSubClasses/ALU.cpp src/CPUSubClasses/ALU.hpp src/Sequencer.cpp src/Sequencer.hpp src/CPUSubClasses/Code.cpp src/CPUSubClasses/Code.hpp src/Memory.cpp src/Memory.hpp)
