// Main Project File
// Created on 07/12/2022 by Vinanddrinks.
// Copyright (c) 2022 Gradling Team. All rights reserved.
#include <iostream>
using namespace std;
#include "FileParsing.hpp"


int main() {
    FileParsing file("ASMFiles/example.txt"); // Create FileParsing object
    file.loadMemory();
    // check memory status
    Memory* mem = Memory::getInstance();
    cout << "Memory status: " << endl;
    for (int i = 0; i < mem->getCurrentSize(); i++) {
        cout << "Address: " << i << " Name: "+mem->getCell(i).name<<" Data: " << mem->get(i) << endl;
    }
    file.loadCode();
    // check code status
    Code* code = Code::getInstance();
    cout << "Code status: " << endl;
    for (int i = 0; i < code->getCodeSize(); i++) {
        cout << "line: " << i << " Op: " << code->getLine(i) << endl;
    }
    return 0;
}