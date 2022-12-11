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
    addInstruction("NOP", "NO","NO", "NO");
    addInstruction("PEEK", "REG", "NO", "NO");
    addInstruction("PEEKN", "REG", "C", "NO");

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
                //Update the line with currentLine -1 because the currentLine has been incremented
                line = this->file->getLine(currentLine-1);
            }
            if(line == keyWord[1]){
                codeSyntax();
                std::cout << "Code syntax is correct" << std::endl;
                continue;
            }
            std::cout << "^^^Error: Unknown keyword^^^" << std::endl;
            continue;
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
    bool data = true;
    while(data and currentLine < file->getLineCount()){
        bool isvar = true;
        //Get the current data line
        line = this->file->getLine(currentLine);
        currentLine++;
        std::cout << line << std::endl;
        //check if the line is a comment or an empty line
        if(line.front() == '#'){
            data = false;
            continue;
        }
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
        //We use line.length()-1 because the last character is a carriage return
        if (i >= line.length() -1) {
            std::cout << "^^^Error: missing value^^^" << std::endl;
            continue;
        }
        //Check if the given value is a number
        while(i < line.length() -1) {
            //std::cout << "char= "<< line[i] << "i" << i << "long= "<< line.length()<< std::endl;
            if ((line[i] < '0' or line[i] > '9' ) and line[i] != '?' and line[i] != ','
            or (line[i] == ',' and (line.length() == i +2  or line[i+1] == ',' or line[i-1] == ' '))
            ) {
                std::cout << "^^^Error: value is not a number^^^" << std::endl;
                break;
            }
            i++;
        }

        //check if the variable name is valid
        for(int j = 0; j < varNumber; j++) {
            if (varName[j] == variableName) {
                std::cout << "^^^Variable already declared^^^" << std::endl;
                isvar = false;
                continue;
            }
        }
        for (int j = 0; j < 20; ++j) {
            if(variableName == instructions[j]->name){
                std::cout << "^^^Error: variable name is a reserved keyword^^^" << std::endl;
                isvar = false;
                continue;
            }
        }
        for (int j = 0; j<6; ++j) {
            if(variableName == REGISTER[j]){
                std::cout <<"^^^Error: variable name is a register name^^^"<< std::endl;
                isvar = false;
                continue;
            }
        }
        if(isvar){
        varName[varNumber] = variableName;
        varNumber++;}
    }

}
// Add an instruction to the instruction list
void SyntaxChecker::addInstruction(std::string name, std::string arg1, std::string arg2, std::string arg3) {
    auto** temp = new Instruction*[instructionCount+1];
    for(int i = 0; i < instructionCount; i++){
        temp[i] = this->instructions[i];
    }
    temp[instructionCount] = new Instruction;
    temp[instructionCount]->name = std::move(name);
    temp[instructionCount]->args[0] = std::move(arg1);
    temp[instructionCount]->args[1] = std::move(arg2);
    temp[instructionCount]->args[2] = std::move(arg3);
    this->instructions = temp;
    instructionCount++;
}

void SyntaxChecker::codeSyntax() {
    //Get the first code line
    std::string line = this->file->getLine(currentLine);
    std::string buffer;
    int instructionIndex;
    //loop until the end of the code section
    bool code = true;
    while(code and currentLine < file->getLineCount()){
        //Get the current code line
        line = this->file->getLine(currentLine);
        currentLine++;
        std::cout << line << std::endl;
        bool isinstr = false;
        //check if the line is a comment or an empty line
        if(line.front() == '!' or line.front() == ' '){
            continue;
        }
        int i = 0;
        buffer  = "";
        //get instruction name
        while (line[i] != ' ' and i < line.length()) {
            buffer += line[i];
            i++;
        }
        //Check if the instruction is valid
        for(int j = 0; j < instructionCount; ++j) {
            if(buffer == instructions[j]->name){
                instructionIndex = j;
                isinstr = true;
            }
        }
        if(!isinstr){
            std::cout << "^^^Error : Invalide Instruction^^^" << std::endl;
        }
        for (int j = 0; j < 3; ++j) {
            //Increment i until we find a value
            while (line[i] == ' ') {
                i++;
            }
            buffer = "";
            while (line[i] != ' ' and i < line.length() -1) {
                buffer += line[i];
                i++;
            }
            if(argValidity(buffer, instructions[instructionIndex]->args[j])){
                continue;
            }
        }

    }
}

//Check if the given argument type is valid
bool SyntaxChecker::argValidity(std::string arg, std::string argtype) {
    //check if the argument is a register
    if(argtype == "REG"){
        for (const auto & i : REGISTER) {
            if(arg == i){
                return true;
            }
        }
    }
    //check if the argument is a variable
    if(argtype == "VAR"){
        for (int i = 0; i < varNumber; ++i) {
            if(arg == varName[i]){
                return true;
            }
        }
    }
    //check if the argument is a const or a register
    if(argtype == "RC"){
        bool isnumber = true;
        for (char i : arg) {
            if(i < '0' or i > '9'){
                isnumber = false;
            }
        }
        if(isnumber){
            return true;
        }
        for (const auto & i : REGISTER) {
            if(arg == i){
                return true;
            }
        }
    }
    if(argtype == "RVC"){

        //Check if the argument is a register
        for (const auto & i : REGISTER) {
            if(arg == i){
                return true;
            }
        }
        //Check if the argument is a variable
        for (int i = 0; i < varNumber; ++i) {
            if(arg == varName[i]){
                return true;
            }
        }
        //Check if the argument is a number
        bool isnumber = true;
        for (char i : arg) {
            if(i < '0' or i > '9'){
                isnumber = false;
            }
        }
        if(isnumber){
            return true;
        }
    }
    //Check if argument is necessary
    if(argtype == "NO"){
        if(arg == ""){
        return true;}
    }
    std::cout << "^^^Error: Invalid argument, expected: " + argtype + "^^^" << std::endl;
    return false;

}