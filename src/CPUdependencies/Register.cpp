// Source file for the register class
// Created by vinanddrinks on 09/12/2022.
// Copyright (c) 2022 Gradling Team. All rights reserved.
#include "CPUdependencies/Register.hpp"

// includes
#include <iostream>
#include <utility>
// definitions
// constructor
Register::Register() {
    this->value = 0;
    this->name = "T0";
}
Register::Register(std::string name) {
    this->value = 0;
    this->name = std::move(name);
}
Register::Register(std::string name, int value) {
    this->value = value;
    this->name = std::move(name);
}

Register::Register(const Register &reg) {
    this->value = reg.getValue();
    this->name = reg.getName();
}
// getters
std::string Register::getName() const {
    return this->name;
}
int Register::getValue() const {
    return this->value;
}
// setters
void Register::setName(std::string t) {
    this->name = std::move(t);
}
void Register::setValue(int i) {
    this->value = i;
}
// overloaded operators
Register& Register::operator=(const Register &reg) = default;

bool Register::operator==(const Register &reg) const {
    return this->name == reg.name && this->value == reg.value;
}
bool Register::operator!=(const Register &reg) const {
    return this->name != reg.name || this->value != reg.value;
}
bool Register::operator<(const Register &reg) const {
    return this->value < reg.value;
}
bool Register::operator>(const Register &reg) const {
    return this->value > reg.value;
}
bool Register::operator<=(const Register &reg) const {
    return this->value <= reg.value;
}
bool Register::operator>=(const Register &reg) const {
    return this->value >= reg.value;
}
std::ostream& operator<<(std::ostream &os, const Register &reg) {
    os << reg.name << ": " << reg.value;
    return os;
}
