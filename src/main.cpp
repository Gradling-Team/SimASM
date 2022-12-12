// Main Project File
// Created on 07/12/2022 by Vinanddrinks.
// Copyright (c) 2022 Gradling Team. All rights reserved.
#include <iostream>
using namespace std;
#include "FileParsing.hpp"
#include "ControlProcessUnit.hpp"
#include "SyntaxChecker.hpp"

int main() {
    string filename;
    cout << "Enter File path" << endl;
    getline(cin,filename);
    if(filename.empty() or filename == "\r" or filename == "\n"){
        filename = "ASMFiles/example.txt";
    }else if(filename.find(".txt") != filename.length()-4){
        filename.append(".txt");
    }
    FileParsing file(filename); // Create FileParsing object
    SyntaxChecker SyntaxChecker(&file); // Create SyntaxChecker object
    SyntaxChecker.checkSyntax(); // Check the syntax of the file
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
    bool stepByStep = false;
    string step;
    while(step != "y" && step != "Y" && step !="n" && step !="N"){
    cout << "Step by Step ? [Y/n]" << endl;
    cin >> step;
    if(step == "y" || step == "Y"){
        std::cout << "Step by step is active" << std::endl;
        stepByStep = true;
    }else if(step == "n" || step == "N"){
        stepByStep = false;
    }
    }

    ControlProcessUnit one;
    one.run(stepByStep);
    cout << "Memory status by adress: " << endl;
    int len = 0;
    for (int i = 0; i < mem->getCurrentSize(); i++) {
        string b = mem->getCell(i).name;
        if(len < b.length()){
            len = b.length();
        }
    }
    for (int i = 0; i < mem->getCurrentSize(); i++) {
        if (mem->getCell(i).name.length() == 1){
            cout << "Address: " << i << " Name: " + mem->getCell(i).name << string(len, ' ') << "Data: " << mem->get(i) << endl;
        }else{
            int tmp = len - (mem->getCell(i).name.length()-1);
        cout << "Address: " << i << " Name: "+mem->getCell(i).name << string(tmp, ' ') <<"Data: " << mem->get(i) << endl;
        }
    }
    // get memory by name
    cout << "Memory status by name :" << endl;
    len = 0;
    for (int i = 0; i < mem->getCurrentSize(); i++) {
        string b = mem->getCell(i).name;
        if(len < b.length()){
            len = b.length();
        }
    }
    for (int i = 0; i < mem->getCurrentSize(); i++) {
        string a = mem->getCell(i).name;
        if(a.length() > 1){
            int tmp = len - (a.length()-1);
        cout << "Adresse: " << mem->getAddr(a) << " Name: " << a << string(tmp,' ') << "Data: " << mem->get(a) << endl;
        }
        if(a.length() == 1){
            cout << "Adresse: " << mem->getAddr(a) << " Name: " << a <<  string(len, ' ') << "Data: " << mem->get(a) << endl;
        }
    }


    return 0;
}