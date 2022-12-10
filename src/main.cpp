// Main Project File
// Created on 07/12/2022 by Vinanddrinks.
// Copyright (c) 2022 Gradling Team. All rights reserved.
#include <iostream>
using namespace std;
#include "FileParsing.hpp"

int main() {
    FileParsing file("ASMFiles/example.txt"); // Create FileParsing object
    for(int i = 0; i < file.getLineCount(); i++) { // Loop through each line in the file
        cout << file.getLine(i) << endl;
    }
    return 0;
}