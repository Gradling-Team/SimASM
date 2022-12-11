// Source File for class SyntaxChecker
// Created by MathieuCtt on 09/12/2022.
// Copyright (c) 2022 Gradling Team. All rights reserved.


#include "SyntaxChecker.hpp"

#include <utility>

// Constructor
SyntaxChecker::SyntaxChecker(FileParsing *file) {
    this->file = file;
    this->varNumber = 0;
    this->instructionCount = 0;
    this->currentLine = 0;
    this->dataStart = 0;
    this->codeStart = 0;
    this->instructions = nullptr;
    addInstruction("LDA", "REG", "RVC", "NO");
    addInstruction("STR", "VAR", "RC", "NO");
    addInstruction("PUSH", "RVC", "NO", "NO");
    addInstruction("POP", "REG", "NO", "NO");
    addInstruction("AND", "REG", "RVC", "NO");
    addInstruction("OR", "REG", "RVC", "NO");
    addInstruction("NOT", "REG", "NO", "NO");
    addInstruction("ADD", "REG", "RVC", "NO");
    addInstruction("SUB", "REG", "RVC", "NO");
    addInstruction("MUL", "REG", "RVC", "NO");
    addInstruction("DIV", "REG", "RVC", "NO");
    addInstruction("MOD", "REG", "RVC", "NO");
    addInstruction("INC", "REG", "NO", "NO");
    addInstruction("DEC", "REG", "NO", "NO");
    addInstruction("BEQ", "RVC", "RVC", "LABEL");
    addInstruction("BNE", "RVC", "RVC", "LABEL");
    addInstruction("BBG", "RVC", "RVC", "LABEL");
    addInstruction("BSM", "RVC", "RVC", "LABEL");
    addInstruction("JMP", "LABEL", "NO", "NO");
    addInstruction("HLT", "NO", "NO", "NO");
}
// Check the syntax of the file
void SyntaxChecker::checkSyntax() {
    currentLine = 0;
    //loop until the end of the file
    while(currentLine < file->getLineCount()){
        //get the current line
        std::string line = this->file->getLine(currentLine);
        //increment the line counter
        currentLine++;
        std::cout << line << std::endl;
        //check if the line is a comment
        if(line.front() == '!'){
            continue;
        }
        //check if the line is a data line
        if(line.front() == '#'){
            //check if we enter the data section
            if(line == keyWord[0]){
                dataSyntax();
                continue;
            }
            if(line == keyWord[1]){
                codeStart = currentLine-1;
                continue;
            }
            std::cout << "^^^Error: Unknown keyword^^^" << std::endl;
        }
        std::cout << "^^^Error: Unknown Syntax error^^^" << std::endl;

    }
}
//destructor
SyntaxChecker::~SyntaxChecker() {
    delete this->instructions;
}
//methods
//Check the syntax of the data section
void SyntaxChecker::dataSyntax(void) {
    //Get the first data line
    std::string line = this->file->getLine(currentLine);
    //Temporary variable to store the variable name
    std::string variableName;
    //loop until the end of the data section
    while(line.front() != '#' and currentLine < file->getLineCount()){
        //Get the current data line
        line = this->file->getLine(currentLine);
        currentLine++;
        std::cout << line << std::endl;
        //check if the line is a comment or an empty line
        if(line.front() == '!' or line.front() == '\r'){
            continue;
        }
        int i = 0;
        variableName = "";
        //get the variable name
        while (line[i] != ' ' and i < line.length()) {
            variableName += line[i];
            i++;
        }
        //Increment i until we find a value
        while (line[i] == ' ') {
            i++;
        }
        //check if there is a value
        if (i >= line.length() -1) {
            std::cout << "^^^Error: missing value^^^" << std::endl;
            continue;
        }
        //Check if the given value is a number
        while(i < line.length() -1) {
            char t = line[i];
            if (line[i] < '0' or line[i] > '9') {
                std::cout << "^^^Error: value is not a number^^^" << std::endl;
                break;
            }
            i++;
        }

        //check if the variable name is valid
        for(int j = 0; j < varNumber; j++) {
            if (varName[j] == variableName) {
                std::cout << "^^^Variable already declared^^^" << std::endl;
                continue;
            }
        }
        varName[varNumber] = variableName;
        varNumber++;
    }
    currentLine--;

}
// Add an instruction to the instruction list
void SyntaxChecker::addInstruction(std::string name, std::string arg1, std::string arg2, std::string arg3) {
    auto** temp = new Instruction*[instructionCount+1];
    for(int i = 0; i < instructionCount; i++){
        temp[i] = this->instructions[i];
    }
    temp[instructionCount] = new Instruction;
    temp[instructionCount]->name = std::move(name);
    temp[instructionCount]->arg1 = std::move(arg1);
    temp[instructionCount]->arg2 = std::move(arg2);
    temp[instructionCount]->arg3 = std::move(arg3);
    this->instructions = temp;
    instructionCount++;
}

