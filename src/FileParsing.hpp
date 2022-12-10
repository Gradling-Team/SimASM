// Header file for FileParsing.cpp
// Created by vinanddrinks on 09/12/2022.
// Copyright (c) 2022 Gradling Team. All rights reserved.

#ifndef SIMASM_FILEPARSING_HPP
#define SIMASM_FILEPARSING_HPP
// includes
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
// class definition
class FileParsing {
public:
    // Constructor
    explicit FileParsing(const std::string& filename);
    // Destructor
    ~FileParsing();
    // Methods
    std::string getLine(); // Get the next line in the file
    std::string getLine(int line); // Get line at line number
    // Getters
    int getLineNum() const;
    int getLineCount() const;
private:
    // Variables
    std::string filename;
    std::ifstream file;
    int lineNum; // current line number
    int lineCount; // Number of lines in file
    // Methods
    int countLines();
};
#endif
