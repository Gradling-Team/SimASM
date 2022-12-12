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
#include "Memory.hpp"
#include "CPUdependencies/Code.hpp"
// class definition
class FileParsing {
public:
    // Constructor
    explicit FileParsing(const std::string& filename);
    // Destructor
    ~FileParsing();
    // Methods
    void loadIntoFileContents(); // Loads the file into a vector of strings all get operations will be done on this vector
    std::string getLine(); // Gets the next line in the file
    std::string getLine(int line); // Gets the line at the specified line number
    int countLines(); // Counts the number of lines in the file
    // Getters
    int getLineNum() const;
    int getLineCount() const;
    // Code and Data Sequencing and loading
    void loadCode(); // Load the code into the Code class
    void loadVar(const std::string& line); // Load a single variable into the Memory class
    void loadArray(const std::string& line); // Load an array into the Memory class
    void loadMemory(); // Load the data into the Memory class
private:
    // Variables
    std::string filename;
    std::ifstream file;
    std::vector<std::string> fileContents;
    int lineNum; // current line number
    int lineCount; // Number of lines in file
    Memory* memPtr;
    Code* codePtr;
};
#endif
