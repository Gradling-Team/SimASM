// Source File for class SyntaxChecker
// Created by MathieuCtt on 09/12/2022.
// Copyright (c) 2022 Gradling Team. All rights reserved.


#include "SyntaxChecker.hpp"

#include <utility>

// Constructor
SyntaxChecker::SyntaxChecker(FileParsing *file) {
    this->file = file;
    this->labelCount = 0;
    this->varCount = 0;
    this->instructionCount = 0;
    this->currentLine = 0;
    this->errorCount = 0;
    this->instructions = nullptr;
    //Initialize the array of instruction
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
    addInstruction("SRL","REG","C","NO");
    addInstruction("SRR","REG","C","NO");
    addInstruction("PEEK", "REG", "NO", "NO");
    addInstruction("PEEKN", "REG", "C", "NO");

}
//Main function to check the syntax of the file,
void SyntaxChecker::checkSyntax() {
    //loop until the end of the file
    while(currentLine < file->getLineCount()){
        //get the current line
        std::string line = this->file->getLine(currentLine);
        //increment the line counter
        currentLine++;
        std::cout << line << std::endl;
        //check if the line is a comment or an empty line and skip it
        if(line.front() == '!' or line == "\r"){
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
                continue;
            }
            std::cout << "^^^Error: Unknown keyword^^^" << std::endl;
            errorCount++;
            continue;
        }
        std::cout << "^^^Error: Unknown Syntax error^^^" << std::endl;
        errorCount++;

    }
    if(errorCount == 0){
        std::cout << "---No error found---" << std::endl;
    }
    else{
        std::cout << "---" << errorCount << " error(s) found---" << std::endl;
    }
}
//destructor
SyntaxChecker::~SyntaxChecker() {
    delete this->instructions;
}
//methods
//Check the syntax of the data section
void SyntaxChecker::dataSyntax() {
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
            errorCount++;
            continue;
        }
        //Check if the given value is a number
        while(i < line.length() -1) {
            //Character may be a number, "?" or "," but it this case "," must be followed and preceded by a number or "?
            if ((line[i] < '0' or line[i] > '9' ) and line[i] != '?' and line[i] != ','
            or (line[i] == ',' and (line.length() == i +2  or line[i+1] == ',' or line[i-1] == ' '))
            ) {
                std::cout << "^^^Error: value is not a number^^^" << std::endl;
                errorCount++;
                break;
            }
            i++;
        }

        //check if the variable name is valid
        for(int j = 0; j < varCount; j++) {
            if (varName[j] == variableName) {
                std::cout << "^^^Variable already declared^^^" << std::endl;
                errorCount++;
                isvar = false;
                continue;
            }
        }
        for (int j = 0; j < instructionCount; ++j) {
            if(variableName == instructions[j]->name){
                std::cout << "^^^Error: variable name is a reserved keyword^^^" << std::endl;
                errorCount++;
                isvar = false;
                continue;
            }
        }
        for (int j = 0; j<4; ++j) {
            if(variableName == REGISTER[j]){
                std::cout <<"^^^Error: variable name is a register name^^^"<< std::endl;
                errorCount++;
                isvar = false;
                continue;
            }
        }
        if(variableName.front()<= '9' and variableName.front() >= '0'){
            std::cout <<"^^^Error: variable can't start with a number^^^"<< std::endl;
            errorCount++;
            isvar = false;
            continue;
        }
        if(isvar){
        varName[varCount] = variableName;
        varCount++;}
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
    int codeSyntaxLine = currentLine;
    //Index of the instruction in the instruction array
    int instructionIndex;
    //Find the labels
    while(currentLine < file->getLineCount()){
        line = this->file->getLine(currentLine);
        currentLine++;
        if(line[line.length()-2]== ':'){
            bool notinlist = true;
            for(int j = 0; j < labelCount; j++){
                if(label[j].name == line){
                    label[j].nbr++;
                    notinlist = false;
                }
            }
            if(notinlist){
                label[labelCount].name = line;
                label[labelCount].nbr = 1;
                labelCount++;
            }
        }
    }
    //loop until the end of the code section
    currentLine = codeSyntaxLine;
    while(currentLine < file->getLineCount()){
        //Get the current code line
        line = this->file->getLine(currentLine);
        currentLine++;
        std::cout << line << std::endl;
        bool isinstr = false;
        //check if the line is a comment or an empty line
        if(line.front() == '!' or line.front() == '\r'){
            continue;
        }
        int i = 0;
        buffer  = "";
        //get instruction name
        while (line[i] != ' ' and i < line.length()) {
            buffer += line[i];
            i++;
        }
        //Continue if the line is a label
        int labelNbr = 0;
        for(int j = 0; j < labelCount; j++){
           if(line == label[j].name){

                isinstr = true;
                //Check if the label is valid
                if(line.front()<='9' and line.front()>='0'){
                    std::cout << "^^^Error: label name can't start with a number^^^" << std::endl;
                    errorCount++;
                    continue;
                }
                for (char i : line) {
                    if(i == ' '){
                        std::cout << "^^^Error: label can't have space^^^" << std::endl;
                        errorCount++;
                        continue;
                    }
                }
                for (int i = 0; i < instructionCount; i++) {
                    if(line == instructions[i]->name + ":\r"){
                        std::cout << "^^^Error: label name is a reserved keyword^^^" << std::endl;
                        errorCount++;
                        continue;
                    }
                }

               if(label[j].nbr > 1){
                   std::cout << "^^^Error: label name appears more than once^^^" << std::endl;
                   errorCount++;
                   continue;
               }
            }
        }
        //todo : créer une variable equivalente à isintr mais pour les labels
        if(isinstr) continue;
        //Check if the instruction is valid
        for(int j = 0; j < instructionCount; ++j) {
            if (buffer == instructions[j]->name) {
                instructionIndex = j;
                isinstr = true;
            }
        }



        if(!isinstr){
            std::cout << "^^^Error : Invalid Instruction^^^" << std::endl;
            errorCount++;
            continue;
        }
        for ( std::string & arg : instructions[instructionIndex]->args) {
            //Increment i until we find a value
            while (line[i] == ' ') {
                i++;
            }
            buffer = "";
            while (line[i] != ' ' and i < line.length() -1) {
                buffer += line[i];
                i++;
            }
            if((instructions[instructionIndex]->name == "LDA" or instructions[instructionIndex]->name == "STR") and arg == "NO"
            and !buffer.empty()){
                arg = "C";
                argValidity(buffer, arg);
                arg = "NO";
                continue;
            }
            if(argValidity(buffer, arg)){
                continue;
            }
        }

    }
}

//Check if the given argument type is valid
bool SyntaxChecker::argValidity(std::string arg, const std::string& argtype) {
    // Check is the argument is an array and delete the brackets
    bool index = false;
    if(arg.back() == ']'){
        arg.pop_back();
        while (arg.back() != '[') {
            if (arg.back() < '0' or arg.back() > '9') {
                std::cout << "^^^Error: array index is not a number or missing '['^^^" << std::endl;
                errorCount++;
                return false;
            }
            if (arg.back() <= '9' and arg.back() >= '0') {
                index = true;
            }
            arg.pop_back();
        }
        arg.pop_back();
        if(!index){
            std::cout << "^^^Error: missing index^^^" << std::endl;
            errorCount++;
            return false;

        }
    }
    //Check if the argument is empty
    if(argtype == "NO"){
        if(arg.empty()){
            return true;}
    }else
        if(arg.empty()){
            std::cout << "^^^Error: missing argument^^^" << std::endl;
            errorCount++;
            return false;
        }
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
        for (int i = 0; i < varCount; ++i) {
            if(arg == varName[i]){
                return true;
            }
        }
    }
    //check if the argument is a const
    if(argtype == "C"){
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
        for (int i = 0; i < varCount; ++i) {
            if(arg == varName[i]){
                return true;
            }
        }
        //Check if the argument is a number
        bool isnumber = true;
        for (char i : arg) {
            if(i < '0' or i > '9' ){
                isnumber = false;
            }
        }
        if(isnumber){
            return true;
        }
    }
    //Check if the argument is a label
    if(argtype == "LABEL"){
        for (int i = 0; i < labelCount; ++i) {

            if(arg + ":\r" == label[i].name){
                return true;
            }
        }
        std::cout << "^^^Error: label not found^^^" << std::endl;
        errorCount++;
        return false;
    }
    //Check if argument is necessary

    std::cout << "^^^Error: Invalid argument, expected: " + argtype + "^^^" << std::endl;
    errorCount++;
    return false;

}