//
// Created by vinanddrinks on 11/12/2022.
//

#ifndef SIMASM_CONTROLPROCESSUNIT_HPP
#define SIMASM_CONTROLPROCESSUNIT_HPP
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "FileParsing.hpp"
#include "CPUdependencies/ArithmeticLogicUnit.hpp"
#include "CPUdependencies/Code.hpp"
#include "CPUdependencies/Register.hpp"
#include "CPUdependencies/StackRegisters.hpp"
#include "Memory.hpp"
// class definition
class ControlProcessUnit {
public:
    // Constructor
    ControlProcessUnit();
    // Destructor
    ~ControlProcessUnit();
    void run();//switch case to select and execute operation
private:
    struct opCode {
        int argNumber;
        int arg1Type;
        int arg2Type;
        int arg3Type;
        std::string op;
        std::string arg1;
        std::string arg2;
        std::string arg3;
    };
    Memory* memPtr;
    Code* codePtr;
    ArithmeticLogicUnit* aluPtr;
    opCode currentOpCode;
    // Methods
    void loadOpCode(const std::string& line);
    void executeOpCode();
    static int getArgType(const std::string& arg); // 0 if register, 1 if memory, 2 if immediate/constant

};


#endif //SIMASM_CONTROLPROCESSUNIT_HPP
