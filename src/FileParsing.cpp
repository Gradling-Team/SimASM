// Source File for class FileParsing
// Created by vinanddrinks on 09/12/2022.
// Copyright (c) 2022 Gradling Team. All rights reserved.

// Includes
#include "FileParsing.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Memory.hpp"
#include "CPUdependencies/Code.hpp"
// Constructor
FileParsing::FileParsing(const std::string& filename) {
    this->file.open(filename);
    // Check if file is open
    if (!this->file.is_open()) {
        std::cerr << "Error: File not found" << std::endl;
        exit(1);
    }
    this->filename = filename;
    loadIntoFileContents();
    this->lineNum = 0;
    this->lineCount = (int)this->fileContents.size();
    this->memPtr = Memory::getInstance();
    this->codePtr = Code::getInstance();
}

// Destructor
FileParsing::~FileParsing() {
    this->file.close();
    this->memPtr = nullptr;
    this->codePtr = nullptr;
}

// Methods
// line getters from fileContents
std::string FileParsing::getLine() {
    std::string line = this->fileContents[this->lineNum];
    this->lineNum++;
    return line;
}
std::string FileParsing::getLine(int line) {
    this->lineNum = line;
    return this->fileContents[line];
}
// loader
void FileParsing::loadIntoFileContents() {
    std::string line;
    while (std::getline(this->file, line)) {
        // remove carriage return if present
        if (line[line.size() - 1] == '\r') {
            line.erase(line.size() - 1);
        }
        // remove next line marker if present
        if (line[line.size() - 1] == '\n') {
            line.erase(line.size() - 1);
        }
        this->fileContents.push_back(line);
    }
}
// Getters
int FileParsing::getLineNum() const {
    return this->lineNum;
}
int FileParsing::getLineCount() const {
    return this->lineCount;
}
// Sequencing function for loading code
// Variable and Array loading functions
// a line containing an array contains "," else it is a variable declaration
// if line contain "?" then it is a lazy variable declaration and will be loaded into memory with value 0
// memory declaration start after the "#DATA" section header and end before the "#CODE" section header
// code loading start after the "#CODE" section header and end at the end of the file.
// comments start with "!" and end at the end of the line, comments are ignored
void FileParsing::loadMemory() {
    std::string line;
    while (this->lineNum < this->lineCount) {
        line = getLine();
        if (line.find("#CODE") != std::string::npos) {
            break;
        }
        if (line.find("#DATA") != std::string::npos) {
            continue;
        }
        if (line.find('!') != std::string::npos) {
            continue;
        }
        if (line.find(',') != std::string::npos) {
            loadArray(line);
        } else {
            loadVar(line);
        }
    }
}
void FileParsing::loadVar(const std::string& line) {
    std::string varName;
    std::string varValue;
    std::stringstream ss(line);
    std::getline(ss, varName, ' ');
    std::getline(ss, varValue, ' ');
    if (varValue.find('?') != std::string::npos) {
        this->memPtr->store(varName, 0);
    } else {
        this->memPtr->store(varName, std::stoi(varValue));
    }
}
void FileParsing::loadArray(const std::string &line) {
    std::string name;
    int** array;
    std::stringstream ss(line);
    // the length of the array is the number of commas in the line + 1
    int length = 1;
    for (char c : line) {
        if (c == ',') {
            length++;
        }
    }
    // get the name of the array
    ss >> name;
    // get the array
    array = new int*[length];
    for (int i = 0; i < length; i++) {
        array[i] = new int[1];
        ss >> array[i][0];
    }
    // store the array in memory
    this->memPtr->storeArray(name, array, length);
}
// Code loading function
void FileParsing::loadCode() {
    // we position ourselves at the beginning of the code section
    FileParsing::getLine(0);
    std::string line;
    while (line != "#CODE") {
        line = getLine();
    }
    // we remember the line number of the first line of code
    int codeStart = this->lineNum;
    // we load the code
    while (this->lineNum < this->lineCount) {
        line = getLine();
        if (line.find('!') != std::string::npos) {
            continue;
        }
        // if line is a label
        if (line.find(':') != std::string::npos) {
            std::string labelName;
            std::stringstream ss(line);
            std::getline(ss, labelName, ':');
            this->codePtr->addLabel(labelName, this->lineNum - codeStart);
            continue;
        }
        this->codePtr->add(line);
    }
}

// End of FileParsing.cpp
