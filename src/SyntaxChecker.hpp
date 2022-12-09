// Header file for SyntaxChecker.cpp
// Created by MathieuCtt on 09/12/2022.
// Copyright (c) 2022 Gradling Team. All rights reserved.


#ifndef SIMASM_SYNTAXCHECKER_HPP
#define SIMASM_SYNTAXCHECKER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "SyntaxSubClasses/Instructions.cpp"


// class definition
class FileParsing {
public:
    // Constructor
    //explicit SyntaxChecking(const std::string& filename);
    // Destructor
    //~SyntaxChecking();
    // Methods
    // Getters
private:
    // Variables
    std::string filename;
    std::ifstream file;
    int lineNum; // current line number
    int lineCount; // Number of lines in file
    //
    const std::string REGISTER[6] = {"T0", "T1", "T2", "T3", "SP", "PC"};
    const std::string keyWord[2] = {"#DATA", "#CODE"};
    const Instructions INSTRUCTION[5] = {
            Instructions("LDA", REG, RVC, NO),
            Instructions("STR",VAR, RC, NO),
            Instructions("PUSH", RVC, NO, NO),
            Instructions("POP", REG, NO, NO),
            Instructions("AND", REG, RVC, NO)
    };


/*
                {"LDA",{REG, RVC, NO}},
                                    {"STR",{VAR, RC, NO}},
                                    {"PUSH",{RVC, NO, NO}},
                                    {"POP",{REG, NO, NO}},
                                    {"AND",{REG, RVC, NO}},
                                    {"OR",{REG, RVC, NO}},
                                    {"NOT",{REG, NO, NO}},
                                    {"ADD",{REG, RVC, NO}},
                                    {"SUB",{REG, RVC, NO}},
                                    {"DIV",{REG, RVC, NO}},
                                    {"MUL",{REG, RVC, NO}},
                                    {"MOD",{REG, RVC, NO}},
                                    {"INC",{REG, NO, NO}},
                                    {"DEC",{REG, NO, NO}},
                                    {"BEQ",{RVC, RVC, LABEL}},
                                    {"BNE",{RVC, RVC, LABEL}},
                                    {"BBG",{RVC, RVC, LABEL}},
                                    {"BSM",{RVC, RVC, LABEL}},
                                    {"JMP",{LABEL, NO}},
                                    {"HLT",{NO, NO}}};*/


    // Methods
    int countLines();
};


#endif //SIMASM_SYNTAXCHECKER_HPP
