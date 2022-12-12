// Header for the StackRegisters Class
// Created by vinanddrinks on 09/12/2022.
// Copyright (c) 2022 Gradling Team. All rights reserved.

#ifndef SIMASM_STACKREGISTERS_HPP
#define SIMASM_STACKREGISTERS_HPP
#include <iostream>
#include <stack>
#include "Register.hpp"
class StackRegisters { // Class for the stack & registers
public:
    StackRegisters(); // Constructor
    ~StackRegisters(); // Destructor
    void push(const Register& reg); // Pushes a register to the stack
    int pop(); // Pops an int from the stack
    int peek(); // Peeks at the top of the stack
    int peekN(int n); // Peeks at the nth element of the stack
    void printStack(); // Prints the stack
    void displayRegisters(); // Displays the registers
    bool isEmpty(); // Checks if the stack is empty
    bool isFull(); // Checks if the stack is full
    int getRegisterValue(const std::string& name); // Gets the value of a register
    Register getRegister(const std::string& name); // Gets a register
    void setRegisterValue(const std::string& name, int value); // Sets the value of a register
    std::string getRegisterName(int index); // Gets the name of a register
    friend std::ostream& operator<<(std::ostream &os, const StackRegisters &stack); // Overloaded operator
    void display() const; // Displays the stack and registers
private:
    std::stack<int> stack; // Stack
    Register registers[8]; // Registers
    const int maxStackSize = 1024; // Max stack size as each int is 4 bytes so 1024 ints = 4096 bytes
    const std::string registerNames[8] = {"T0", "T1", "T2", "T3", "PC","SP","TMP","TMP2"}; // Register names
    // T registers are multipurpose registers
    // PC is the program counter
    // SP is the stack pointer
    // TMP TMP2 are temporary registers used for holding direct addressed memory values and constant.

};


#endif //SIMASM_STACKREGISTERS_HPP
