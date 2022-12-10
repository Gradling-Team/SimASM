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

void SyntaxChecker::checkSyntax() {
    currentLine = 0;
    while(currentLine < file->getLineCount()){
        std::string line = this->file->getLine(currentLine);
        currentLine++;
        std::cout << line << std::endl;
        if(line.front() == '!'){
            continue;
        }
        if(line.front() == '#'){
            if(line == keyWord[0]){
                dataSyntax();
                currentLine++;
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
void SyntaxChecker::dataSyntax(void) {
    std::string line = this->file->getLine(currentLine);
    std::string variableName;
    while(line.front() != '#' and currentLine < file->getLineCount()){
        line = this->file->getLine(currentLine);
        std::cout << line << std::endl;
        if(line.front() == '!' or line.front() == '\r'){
            currentLine++;
            line = this->file->getLine(currentLine);
            continue;
        }
        int i = 0;
        variableName = "";
        while (line[i] != ' ') {
            variableName += line[i];
            i++;
            if (i >= line.length()) {
                std::cout << "^^^Error: missing value^^^" << std::endl;
                currentLine++;
                break;
            }
        }
        for(int j = 0; j < varNumber; j++) {
            if (varName[j] == variableName) {
                std::cout << "^^^Variable already declared^^^" << std::endl;
                continue;
            }
        }
        //todo (demain): la dernière variable est squeezée en cas de missing value ou je sais pas trop quand, bonne nuit
        currentLine++;
        varName[varNumber] = variableName;
        varNumber++;
    }
    currentLine--;

}

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

