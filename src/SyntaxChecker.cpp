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
// Add an instruction to the instruction list of instruction
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
        if(line.front() == '!' or line.empty()){
            continue;
        }
        //check if the line is section line
        if(line.front() == '#'){
            //check if we enter the data section
            if(line == keyWord[0]){
                //check the syntax of the data section
                dataSyntax();
                //Update the line with currentLine -1 because the currentLine has been incremented
                line = this->file->getLine(currentLine-1);
            }
            //check if we enter the code section
            if(line == keyWord[1]){
                //check the syntax of the code section
                codeSyntax();
                continue;
            }
            //If it's not data section or code section, it's an error
            std::cout << "^^^Error: Unknown keyword^^^" << std::endl;
            errorCount++;
            continue;
        }
        //If it's not a comment, an empty line or a section line, it's an error
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
    //Store each line of the data section
    std::string line;
    //Temporary variable to store the variable name
    std::string variableName;
    //loop until the end of the data section
    bool data = true;
    while(data and currentLine < file->getLineCount()){
        //Set to false if the variable name isn't valid and can't go directly to the next line
        bool isvar = true;
        //Get the current data line
        line = this->file->getLine(currentLine);
        currentLine++;
        std::cout << line << std::endl;
        //If we find a new key word
        if(line.front() == '#'){
            data = false;
            continue;
        }
        //check if the line is a comment or an empty line
        if(line.front() == '!' or line.empty()){
            continue;
        }
        //get the variable name
        int i = 0;
        variableName = "";
        while (line[i] != ' ' and i < line.length()) {
            variableName += line[i];
            i++;
        }
        //Increment i until we find a value
        while (line[i] == ' ') {
            i++;
        }
        //check if there is a value
        //We use line.length() to check if we are
        if (i >= line.length()) {
            std::cout << "^^^Error: missing value^^^" << std::endl;
            errorCount++;
            continue;
        }
        //Check if the given value is a number
        while(i < line.length()) {
            //Character may be a number, "?" or "," but it this case "," must be followed and preceded by a number or "?
            if ((line[i] < '0' or line[i] > '9' ) and line[i] != '?' and line[i] != ','
            or (line[i] == ',' and (line.length() == i +1  or line[i+1] == ',' or line[i-1] == ' '))
            ) {
                std::cout << "^^^Error: value is not a number^^^" << std::endl;
                errorCount++;
                break;
            }
            i++;
        }

        //check if the variable name is valid
        //The variable may be already declared
        for(int j = 0; j < varCount; j++) {
            if (varName[j] == variableName) {
                std::cout << "^^^Variable already declared^^^" << std::endl;
                errorCount++;
                isvar = false;
                continue;
            }
        }
        //tHe variable may be a reserved word
        for (int j = 0; j < instructionCount; ++j) {
            if(variableName == instructions[j]->name){
                std::cout << "^^^Error: variable name is a reserved keyword^^^" << std::endl;
                errorCount++;
                isvar = false;
                continue;
            }
        }
        //The variable may be a name of register
        for (int j = 0; j<4; ++j) {
            if(variableName == REGISTER[j]){
                std::cout <<"^^^Error: variable name is a register name^^^"<< std::endl;
                errorCount++;
                isvar = false;
                continue;
            }
        }
        //The variable may be start with a number
        if(variableName.front()<= '9' and variableName.front() >= '0'){
            std::cout <<"^^^Error: variable can't start with a number^^^"<< std::endl;
            errorCount++;
            isvar = false;
            continue;
        }
        //If isvar is still true we add it to the variable list
        if(isvar){
        varName[varCount] = variableName;
        varCount++;}
    }

}

// Check the syntax of the code section
void SyntaxChecker::codeSyntax() {
    //Get the first code line
    std::string line = this->file->getLine(currentLine);
    //Buffer will be used to store code, word by word
    std::string buffer;
    //Store the line where code start
    int codeSyntaxLine = currentLine;
    //Index of the instruction in the instruction array
    int instructionIndex;
    //Before checking the syntax line by line we store the labels
    while(currentLine < file->getLineCount()){
        //get the first code line
        line = this->file->getLine(currentLine);
        currentLine++;
        //The line is a label if the last character is a ":"
        if(line[line.length()-1]== ':'){
            //we add it to the list only if it's not already in the list
            bool notinlist = true;
            //Go through the label list
            for(int j = 0; j < labelCount; j++){
                if(label[j].name == line){
                    //If the label is in the list we increment the number of time it's used
                    label[j].nbr++;
                    notinlist = false;
                }
            }
            //Add it to the list
            if(notinlist){
                label[labelCount].name = line;
                label[labelCount].nbr = 1;
                labelCount++;
            }
        }
    }
    //now we can loop until the end of the code section
    currentLine = codeSyntaxLine;
    while(currentLine < file->getLineCount()){
        //Get the current code line
        line = this->file->getLine(currentLine);
        currentLine++;
        std::cout << line << std::endl;
        bool isLabel = false;
        //check if the line is a comment or an empty line
        if(line.front() == '!' or line.empty()){
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
        //Go through the label list
        for(int j = 0; j < labelCount; j++){
           if(line == label[j].name){
                //If we find it, the line is a label
                isLabel = true;
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
                    if(line == instructions[i]->name){
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
        //If the line is a label we continue
        if(isLabel) continue;
        //Check if the instruction is valid
        bool isinstr = false;
        //Check if the instruction exists
        for(int j = 0; j < instructionCount; ++j) {
            if (buffer == instructions[j]->name) {
                instructionIndex = j;
                isinstr = true;
            }
        }
        //else, print an error message
        if(!isinstr){
            std::cout << "^^^Error : Invalid Instruction^^^" << std::endl;
            errorCount++;
            continue;
        }
        //The instruction is valid, we check the arguments
        for ( std::string & arg : instructions[instructionIndex]->args) {
            //Increment i until we find a value
            while (line[i] == ' ') {
                i++;
            }
            //fill the buffer with the value
            buffer = "";
            while (line[i] != ' ' and i < line.length()) {
                buffer += line[i];
                i++;
            }
            //Check if the function is overloaded
            //It is the case for LDA and STR, if a third argument is present, then change the type to "C"
            if((instructions[instructionIndex]->name == "LDA" or instructions[instructionIndex]->name == "STR") and arg == "NO"
            and !buffer.empty()){
                arg = "C";
                //CHeck the validity of the argument
                argValidity(buffer, arg);
                //Put it back to NO
                arg = "NO";
                continue;
            }
            //Here the function is not overloaded
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
        //Until the first bracket is found, the argument must be a number
        while (arg.back() != '[') {
            if (arg.back() < '0' or arg.back() > '9') {
                std::cout << "^^^Error: array index is not a number or missing '['^^^" << std::endl;
                errorCount++;
                return false;
            }
            else{
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