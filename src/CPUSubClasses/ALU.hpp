// Header File for the ALU class
// Created by vinanddrinks on 09/12/2022.
// Copyright (c) 2022 Gradling Team. All rights reserved.

#ifndef SIMASM_ALU_HPP
#define SIMASM_ALU_HPP
#include <iostream>
#include "StackRegisters.hpp"
#include "Code.hpp"
#include "../Memory.hpp"
class ALU { // Arithmetic Logic Unit for the CPU simulator
public:
    ALU(); // Constructor
    ~ALU(); // Destructor
    //logical
    void AND(const std::string& r1, const std::string& r2); // ANDs two registers/constant
    void OR(const std::string& r1, const std::string& r2); // ORs two registers/constant
    void NOT(const std::string& r1); // NOTs a register
    //arithmetic
    void ADD(const std::string& r1, const std::string& r2); // Adds two registers/constant
    void SUB(const std::string& r1, const std::string& r2); // Subtracts two registers/constant
    void MUL(const std::string& r1, const std::string& r2); // Multiplies two registers/constant
    void DIV(const std::string& r1, const std::string& r2); // Divides two registers/constant
    void MOD(const std::string& r1, const std::string& r2); // Modulos two registers/constant
    void INC(const std::string& r1); // Increments a register
    void DEC(const std::string& r1); // Decrements a register
    //control and jump
    void BEQ(const std::string& r1, const std::string& r2,const std::string& label); // Branches if equal
    void BNE(const std::string& r1, const std::string& r2,const std::string& label); // Branches if not equal
    void BBG(const std::string& r1, const std::string& r2,const std::string& label); // Branches if bigger
    void BSM(const std::string& r1, const std::string& r2,const std::string& label); // Branches if smaller
    void JMP(const std::string& label); // Jumps to a label
    //stack
    void PUSH(const std::string& r1); // Pushes a register onto the stack
    void POP(const std::string& r1); // Pops a register off the stack
    void PEEK(const std::string& r1); // Peeks at the top of the stack
    void PEEKN(const std::string& r1, int n); // Peeks at the nth element of the stack
    //misc
    void SRR(const std::string& r1,int i); // Shifts a register right
    void SRL(const std::string& r1,int i); // Shifts a register left
    void NOP(); // No operation
    //memory
    void LDA(const std::string& r1, const std::string& a1); // Loads a register from memory
    void STR(const std::string& r1, std::string a1); // Stores a register to memory
    // indirect memory load/store
    void LDA(const std::string& r1, const std::string& a1, const std::string& shift); // Loads a register from memory indirectly
    void STR(const std::string& r1, const std::string& a1, const std::string& shift); // Stores a register to memory indirectly
    // Halt
    void HLT(); // Halts the program
private:
    StackRegisters * stackRegisters{}; // The registers and stack
    Code * code; // The code
    Memory * memory; // The memory
    // Methods
    void jumpToLabel(const std::string &label); // Jumps to a label
};


#endif //SIMASM_ALU_HPP
