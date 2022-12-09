// Source File for class FileParsing
// Created by vinanddrinks on 09/12/2022.
// Copyright (c) 2022 Gradling Team. All rights reserved.

// Includes
#include "FileParsing.hpp"

// Constructor
FileParsing::FileParsing(const std::string& filename) {
    this->file.open(filename);
    // Check if file is open
    if (!this->file.is_open()) {
        std::cerr << "Error: File not found" << std::endl;
        exit(1);
    }
    this->lineNum = 0;
    this->lineCount = countLines();
}

// Destructor
FileParsing::~FileParsing() {
    this->file.close();
}

// Methods
std::string FileParsing::getLine() {
    std::string lineStr;
    std::getline(this->file, lineStr);
    this->lineNum++;
    return lineStr;
}

std::string FileParsing::getLine(int line) {
    //reset fileStream Status
    this->file.clear();
    std::string lineStr;
    this->file.seekg(0, std::ios::beg);
    for (int i = 0; i < line; i++) {
        std::getline(this->file, lineStr);
    }
    this->lineNum = line;
    return lineStr;
}
int FileParsing::countLines() {
    //reset fileStream Status
    this->file.clear();
    std::string lineStr;
    int lineCount = 0;
    while (std::getline(this->file, lineStr)) {
        lineCount++;
    }
    //Reset fileStream Status
    this->file.clear();//clear any errors
    this->file.seekg(0, std::ios::beg);//back to the start!
    return lineCount;
}

// Getters
int FileParsing::getLineNum() const {
    return this->lineNum;
}
int FileParsing::getLineCount() const {
    return this->lineCount;
}

// End of FileParsing.cpp
