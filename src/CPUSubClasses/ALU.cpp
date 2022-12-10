// Source file for the ALU class
// Created by vinanddrinks on 09/12/2022.
// Copyright (c) 2022 Gradling Team. All rights reserved.

#include "ALU.hpp"
#include <utility>
#include "Code.hpp"
// Constructor
ALU::ALU() {
    this->code = Code::getInstance();
    this->memory = Memory::getInstance();
    this->stackRegisters = new StackRegisters();
}
// Destructor
ALU::~ALU() = default;
// Methods
// logical and arithmetic operations
void ALU::AND(const std::string& r1, const std::string& r2){
    stackRegisters->setRegisterValue(r1, stackRegisters->getRegisterValue(r1) & stackRegisters->getRegisterValue(r2));
}
void ALU::OR(const std::string& r1, const std::string& r2){
    stackRegisters->setRegisterValue(r1, stackRegisters->getRegisterValue(r1) | stackRegisters->getRegisterValue(r2));
}
void ALU::NOT(const std::string& r1) {
    stackRegisters->setRegisterValue(r1, ~stackRegisters->getRegisterValue(r1));
}
void ALU::ADD(const std::string& r1, const std::string& r2) {
    stackRegisters->setRegisterValue(r1, stackRegisters->getRegisterValue(r1) + stackRegisters->getRegisterValue(r2));
}
void ALU::SUB(const std::string& r1, const std::string& r2) {
    stackRegisters->setRegisterValue(r1, stackRegisters->getRegisterValue(r1) - stackRegisters->getRegisterValue(r2));
}
void ALU::MUL(const std::string& r1, const std::string& r2) {
    stackRegisters->setRegisterValue(r1, stackRegisters->getRegisterValue(r1) * stackRegisters->getRegisterValue(r2));
}
void ALU::DIV(const std::string& r1, const std::string& r2) {
    stackRegisters->setRegisterValue(r1, stackRegisters->getRegisterValue(r1) / stackRegisters->getRegisterValue(r2));
}
void ALU::MOD(const std::string& r1, const std::string& r2) {
    stackRegisters->setRegisterValue(r1, stackRegisters->getRegisterValue(r1) % stackRegisters->getRegisterValue(r2));
}
void ALU::INC(const std::string& r1) {
    stackRegisters->setRegisterValue(r1, stackRegisters->getRegisterValue(r1) + 1);
}
void ALU::DEC(const std::string& r1) {
    stackRegisters->setRegisterValue(r1, stackRegisters->getRegisterValue(r1) - 1);
}
// Jump under condition
// subfonction jumpToLabel
void ALU::jumpToLabel(const std::string& label) {
    // get the line number of the label
    int line = code->getLabelLineNumber(label);
    // set the program counter to the line number
    stackRegisters->setRegisterValue("PC", line);
}
void ALU::BEQ(const std::string& r1, const std::string& r2, const std::string& label) {
    if(stackRegisters->getRegisterValue(r1) == stackRegisters->getRegisterValue(r2)) {

    }
}
void ALU::BNE(const std::string& r1, const std::string& r2, const std::string& label) {
    if(stackRegisters->getRegisterValue(r1) != stackRegisters->getRegisterValue(r2)) {

    }
}
void ALU::BBG(const std::string& r1, const std::string& r2, const std::string& label) {
    if(stackRegisters->getRegisterValue(r1) >= stackRegisters->getRegisterValue(r2)) {

    }
}
void ALU::BSM(const std::string& r1, const std::string& r2, const std::string& label) {
    if(stackRegisters->getRegisterValue(r1) < stackRegisters->getRegisterValue(r2)) {

    }
}
void ALU::JMP(const std::string& label) {
    jumpToLabel(label);
}
// stack operations
void ALU::PUSH(const std::string& r1) {
    stackRegisters->push(stackRegisters->getRegister(r1));
}
void ALU::POP(const std::string& r1) {
    stackRegisters->setRegisterValue(r1, stackRegisters->pop());
}
void ALU::PEEK(const std::string& r1) {
    stackRegisters->setRegisterValue(r1, stackRegisters->peek());
}
void ALU::PEEKN(const std::string& r1, int n) {
    stackRegisters->setRegisterValue(r1, stackRegisters->peekN(n));
}
// Miscellaneous operations
void ALU::NOP() {
    // do nothing
}
void ALU::SRR(const std::string& r1, const int i) {
    stackRegisters->setRegisterValue(r1, stackRegisters->getRegisterValue(r1) >> i);
}
void ALU::SRL(const std::string& r1, const int i) {
    stackRegisters->setRegisterValue(r1, stackRegisters->getRegisterValue(r1) << i);
}
// memory operations
void ALU::LDA(const std::string& r1, const std::string& a1) {
    stackRegisters->setRegisterValue(r1, memory->get(a1));
}
void ALU::STR(const std::string& r1, std::string a1) {
    memory->store(std::move(a1), stackRegisters->getRegisterValue(r1));
}
void ALU::LDA(const std::string& r1, const std::string& a1, const std::string& shift) {
    stackRegisters->setRegisterValue(r1, memory->get(a1, stoi(shift)));
}
void ALU::STR(const std::string& r1, const std::string& a1, const std::string& shift) {
    memory->store(a1, stackRegisters->getRegisterValue(r1), stoi(shift));
}
// program stop
void ALU::HLT() {
    // stop the program
    stackRegisters->setRegisterValue("PC", -1);
}

