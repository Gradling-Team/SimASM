// Source file for the ArithmeticLogicUnit class
// Created by vinanddrinks on 09/12/2022.
// Copyright (c) 2022 Gradling Team. All rights reserved.

#include "ArithmeticLogicUnit.hpp"
#include <utility>
#include "Code.hpp"
// Constructor
ArithmeticLogicUnit::ArithmeticLogicUnit() {
    this->code = Code::getInstance();
    this->memory = Memory::getInstance();
    this->stackRegisters = new StackRegisters();
}
// Destructor
ArithmeticLogicUnit::~ArithmeticLogicUnit() = default;
// Methods
// logical and arithmetic operations
void ArithmeticLogicUnit::AND(const std::string& r1, const std::string& r2){
    stackRegisters->setRegisterValue(r1, stackRegisters->getRegisterValue(r1) & stackRegisters->getRegisterValue(r2));
}
void ArithmeticLogicUnit::OR(const std::string& r1, const std::string& r2){
    stackRegisters->setRegisterValue(r1, stackRegisters->getRegisterValue(r1) | stackRegisters->getRegisterValue(r2));
}
void ArithmeticLogicUnit::NOT(const std::string& r1) {
    stackRegisters->setRegisterValue(r1, ~stackRegisters->getRegisterValue(r1));
}
void ArithmeticLogicUnit::ADD(const std::string& r1, const std::string& r2) {
    stackRegisters->setRegisterValue(r1, stackRegisters->getRegisterValue(r1) + stackRegisters->getRegisterValue(r2));
}
void ArithmeticLogicUnit::SUB(const std::string& r1, const std::string& r2) {
    stackRegisters->setRegisterValue(r1, stackRegisters->getRegisterValue(r1) - stackRegisters->getRegisterValue(r2));
}
void ArithmeticLogicUnit::MUL(const std::string& r1, const std::string& r2) {
    stackRegisters->setRegisterValue(r1, stackRegisters->getRegisterValue(r1) * stackRegisters->getRegisterValue(r2));
}
void ArithmeticLogicUnit::DIV(const std::string& r1, const std::string& r2) {
    stackRegisters->setRegisterValue(r1, stackRegisters->getRegisterValue(r1) / stackRegisters->getRegisterValue(r2));
}
void ArithmeticLogicUnit::MOD(const std::string& r1, const std::string& r2) {
    stackRegisters->setRegisterValue(r1, stackRegisters->getRegisterValue(r1) % stackRegisters->getRegisterValue(r2));
}
void ArithmeticLogicUnit::INC(const std::string& r1) {
    stackRegisters->setRegisterValue(r1, stackRegisters->getRegisterValue(r1) + 1);
}
void ArithmeticLogicUnit::DEC(const std::string& r1) {
    stackRegisters->setRegisterValue(r1, stackRegisters->getRegisterValue(r1) - 1);
}
// Jump under condition
// subfonction jumpToLabel
void ArithmeticLogicUnit::jumpToLabel(const std::string& label) {
    // get the line number of the label
    int line = code->getLabelLineNumber(label);
    // set the program counter to the line number
    stackRegisters->setRegisterValue("PC", line);
}
void ArithmeticLogicUnit::BEQ(const std::string& r1, const std::string& r2, const std::string& label) {
    if(stackRegisters->getRegisterValue(r1) == stackRegisters->getRegisterValue(r2)) {
        jumpToLabel(label);
    }
}
void ArithmeticLogicUnit::BNE(const std::string& r1, const std::string& r2, const std::string& label) {
    if(stackRegisters->getRegisterValue(r1) != stackRegisters->getRegisterValue(r2)) {
        jumpToLabel(label);
    }
}
void ArithmeticLogicUnit::BBG(const std::string& r1, const std::string& r2, const std::string& label) {
    if(stackRegisters->getRegisterValue(r1) >= stackRegisters->getRegisterValue(r2)) {
        jumpToLabel(label);
    }
}
void ArithmeticLogicUnit::BSM(const std::string& r1, const std::string& r2, const std::string& label) {
    if(stackRegisters->getRegisterValue(r1) < stackRegisters->getRegisterValue(r2)) {
        jumpToLabel(label);
    }
}
void ArithmeticLogicUnit::JMP(const std::string& label) {
    jumpToLabel(label);
}
// stack operations
void ArithmeticLogicUnit::PUSH(const std::string& r1) {
    stackRegisters->push(stackRegisters->getRegister(r1));
}
void ArithmeticLogicUnit::POP(const std::string& r1) {
    stackRegisters->setRegisterValue(r1, stackRegisters->pop());
}
void ArithmeticLogicUnit::PEEK(const std::string& r1) {
    stackRegisters->setRegisterValue(r1, stackRegisters->peek());
}
void ArithmeticLogicUnit::PEEKN(const std::string& r1, int n) {
    stackRegisters->setRegisterValue(r1, stackRegisters->peekN(n));
}
// Miscellaneous operations
void ArithmeticLogicUnit::NOP() {
    // do nothing
}
void ArithmeticLogicUnit::SRR(const std::string& r1, const int i) {
    stackRegisters->setRegisterValue(r1, stackRegisters->getRegisterValue(r1) >> i);
}
void ArithmeticLogicUnit::SRL(const std::string& r1, const int i) {
    stackRegisters->setRegisterValue(r1, stackRegisters->getRegisterValue(r1) << i);
}
// memory operations
void ArithmeticLogicUnit::LDA(const std::string& r1, const std::string& a1) {
    stackRegisters->setRegisterValue(r1, stackRegisters->getRegisterValue(a1));
}
void ArithmeticLogicUnit::STR(const std::string& a1, const std::string& r1) {
    memory->store(a1, stackRegisters->getRegisterValue(r1));

}
void ArithmeticLogicUnit::LDA(const std::string& r1, const std::string& a1, const std::string& shift) {
    stackRegisters->setRegisterValue(r1, memory->get(a1, stoi(shift)));
}
void ArithmeticLogicUnit::STR(const std::string& a1, const std::string& r1, const std::string& shift) {
    memory->store(a1, stackRegisters->getRegisterValue(r1), stoi(shift));
}
// program stop
void ArithmeticLogicUnit::HLT() {
    // stop the program
    stackRegisters->setRegisterValue("PC", -1);
}

// getter
// return the value of the register
int ArithmeticLogicUnit::getRegisterValue(const std::string& r1) {
    return stackRegisters->getRegisterValue(r1);
}
int ArithmeticLogicUnit::getPC(){
    return stackRegisters->getRegisterValue("PC");
}
// set TMP registers
void ArithmeticLogicUnit::setTMP(int i) {
    stackRegisters->setRegisterValue("TMP", i);
}
// set TMP2 registers
void ArithmeticLogicUnit::setTMP2(int i) {
    stackRegisters->setRegisterValue("TMP2", i);
}
// increment the program counter
void ArithmeticLogicUnit::incPC() {
    stackRegisters->setRegisterValue("PC", stackRegisters->getRegisterValue("PC") + 1);
}

void ArithmeticLogicUnit::displayStatus() {
    stackRegisters->display();
}


// Memory.cpp