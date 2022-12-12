// Source file for the StackRegisters class
// Created by vinanddrinks on 09/12/2022.
// Copyright (c) 2022 Gradling Team. All rights reserved.

#include "StackRegisters.hpp"

// Constructor
StackRegisters::StackRegisters() {
    this->stack = std::stack<int>();
    for (int i = 0; i < 8; i++) {
        this->registers[i] = Register(registerNames[i], 0);
    }
}
// Destructor
StackRegisters::~StackRegisters() = default;
// Methods
void StackRegisters::push(const Register& reg) {
    this->stack.push(reg.getValue());
}
int StackRegisters::pop() {
    int value = this->stack.top();
    this->stack.pop();
    return value;
}
int StackRegisters::peek() {
    return this->stack.top();
}
int StackRegisters::peekN(int n) {
    std::stack<int> tempStack = this->stack;
    for (int i = 0; i < n; i++) {
        tempStack.pop();
    }
    return tempStack.top();
}
// display
void StackRegisters::printStack() {
    std::stack<int> temp = this->stack;
    while (!temp.empty()) {
        std::cout << temp.top() << std::endl;
        temp.pop();
    }
}
void StackRegisters::displayRegisters() {
    for (int i = 0; i < 8; i++) {
        std::cout << this->registers[i].getName() << ": " << this->registers[i].getValue() << std::endl;
    }
}
// checks
bool StackRegisters::isEmpty() {
    return this->stack.empty();
}
bool StackRegisters::isFull() {
    return this->stack.size() == this->maxStackSize;
}
// getters
int StackRegisters::getRegisterValue(const std::string& name) {
    for (const auto & i : this->registers) {
        if (i.getName() == name) {
            return i.getValue();
        }
    }
    return -1;
}
Register StackRegisters::getRegister(const std::string& name) {
    for (const auto & i : this->registers) {
        if (i.getName() == name) {
            return i;
        }
    }
    return {"ERROR", -1};
}
std::string StackRegisters::getRegisterName(int value) {
    for (const auto & i : this->registers) {
        if (i.getValue() == value) {
            return i.getName();
        }
    }
    return "ERROR";
}
// setters
void StackRegisters::setRegisterValue(const std::string& name, int value) {
    for (auto & i : this->registers) {
        if (i.getName() == name) {
            i.setValue(value);
        }
    }
}
