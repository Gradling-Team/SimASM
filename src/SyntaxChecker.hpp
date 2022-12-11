// Header file for SyntaxChecker.cpp
// Created by MathieuCtt on 09/12/2022.
// Copyright (c) 2022 Gradling Team. All rights reserved.


#ifndef SIMASM_SYNTAXCHECKER_HPP
#define SIMASM_SYNTAXCHECKER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "FileParsing.hpp"


// class definition
class SyntaxChecker {
public:
    // Constructor
    explicit SyntaxChecker(FileParsing *file);
    // Destructor
    ~SyntaxChecker();
    // Methods
    void checkSyntax();
    // Getters
private:
    struct Instruction{
        std::string name;
        std::string args[3];
    };
    //variables
    std::string varName[100];
    int varNumber;
    int dataStart;
    int codeStart;
    FileParsing * file;
    int currentLine;
    int instructionCount;
    Instruction** instructions;
    // Methods
    bool argValidity(std::string argtype, std::string arg);
    void dataSyntax(void);
    void codeSyntax(void);
    void addInstruction(std::string name, std::string arg1, std::string arg2, std::string arg3);
    // Constants
    const std::string REGISTER[6] = {"T0", "T1", "T2", "T3", "SP", "PC"};
    const std::string keyWord[2] = {"#DATA\r", "#CODE\r"};
};

#endif
