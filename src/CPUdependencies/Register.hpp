// Header file for the Register class
// Created by vinanddrinks on 09/12/2022.
// Copyright (c) 2022 Gradling Team. All rights reserved.

#ifndef SIMASM_REGISTER_HPP
#define SIMASM_REGISTER_HPP

#include <iostream>

class Register{ // This class define a register for the simulator
public:
    Register(); // Default constructor
    Register(std::string name, int value); // Constructor with name and value
    explicit Register(std::string name); // Constructor with name
    Register(const Register &reg); // Copy constructor

    // Getters
    std::string getName() const;
    int getValue() const;

    // Setters
    void setName(std::string t);
    void setValue(int i);

    // Overloaded operators
    Register& operator=(const Register &reg);
    bool operator==(const Register &reg) const;
    bool operator!=(const Register &reg) const;
    bool operator<(const Register &reg) const;
    bool operator>(const Register &reg) const;
    bool operator<=(const Register &reg) const;
    bool operator>=(const Register &reg) const;
    friend std::ostream& operator<<(std::ostream &os, const Register &reg);
private:
    std::string name; // The name of the register
    int value; // The value of the register
};


#endif //SIMASM_REGISTER_HPP
