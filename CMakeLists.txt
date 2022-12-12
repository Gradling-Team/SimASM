cmake_minimum_required(VERSION 3.18)
project(SimASM)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include_directories(src/SyntaxSubClasses)
include_directories(src/CPUdependencies)
add_executable(SimASM src/main.cpp
        src/SyntaxChecker.hpp 
        src/SyntaxChecker.cpp 
        src/FileParsing.hpp 
        src/FileParsing.cpp 
        src/CPUdependencies/StackRegisters.cpp 
        src/CPUdependencies/StackRegisters.hpp 
        src/CPUdependencies/Register.cpp 
        src/CPUdependencies/Register.hpp 
        src/CPUdependencies/ArithmeticLogicUnit.cpp 
        src/CPUdependencies/ArithmeticLogicUnit.hpp 
        src/CPUdependencies/Code.cpp 
        src/CPUdependencies/Code.hpp 
        src/Memory.cpp src/Memory.hpp 
        src/ControlProcessUnit.cpp 
        src/ControlProcessUnit.hpp)
