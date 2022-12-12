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
    // type used to store the labels and the number of time, each one appears in the file
    struct Label {
        std::string name;
        int nbr;
    };
    // type used to store the instructions and the type of each argument
    struct Instruction{
        std::string name;
        std::string args[3];
    };
    //variables
    //Array of variable
    std::string varName[100];
    //Number of variable in the array
    int varCount;
    //Array of label
    Label label[100];
    //Number of label in the array
    int labelCount;
    //Numer of error in the file
    int errorCount;
    //fil use to check the syntax
    FileParsing * file;
    //Current line in the file
    int currentLine;
    //Array used to store the instruction
    Instruction** instructions;
    //Number of instruction in the array
    int instructionCount;
    // Methods
    //take the type of argument expected and an argument, return true if the argument is of the expected type
    bool argValidity(std::string argtype, const std::string& arg);
    //Check the syntax of the data section
    void dataSyntax();
    //Check the syntax of the code section
    void codeSyntax();
    //add the instruction to the array
    void addInstruction(std::string name, std::string arg1, std::string arg2, std::string arg3);
    // Constants
    const std::string REGISTER[6] = {"T0", "T1", "T2", "T3"};
    const std::string keyWord[2] = {"#DATA\r", "#CODE\r"};
};

#endif
