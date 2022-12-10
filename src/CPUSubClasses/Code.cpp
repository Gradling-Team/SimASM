//
// Created by vinanddrinks on 09/12/2022.
//

#include "Code.hpp"
#include <utility>
// instance definition
Code * Code::instancePtr = nullptr;
//constructor
Code::Code() {
    //initialise the variables
    this->code = nullptr;
    this->codeSize = 0;
    this->labelCount = 0;
}
//destructor
Code::~Code() {
    //delete the code
    delete[] this->code;
}
//get instance
Code* Code::getInstance() {
    //create a new instance if it doesn't exist
    if (Code::instancePtr == nullptr) {
        Code::instancePtr = new Code();
    }
    //return the instance
    return Code::instancePtr;
}
//clear
void Code::clear() {
    //delete the code
    delete[] this->code;
    //delete the labels
    delete[] this->labels;
    //set the code to null
    this->code = nullptr;
    //set the code size to 0
    this->codeSize = 0;
    //set the label count to 0
    this->labelCount = 0;
}
//add a line to the code
void Code::add(std::string line) {
    //create a new array of strings
    auto *newCode = new std::string[this->codeSize + 1];
    //copy the old code into the new array
    for (int i = 0; i < this->codeSize; i++) {
        newCode[i] = this->code[i];
    }
    //add the new line to the end of the array
    newCode[this->codeSize] = std::move(line);
    //delete the old code
    delete[] this->code;
    //set the code to the new code
    this->code = newCode;
    //increment the code size
    this->codeSize++;
}
//add a label to the code
void Code::addLabel(std::string name, int lineNumber) {
    //create a new array of labels
    auto *newLabels = new Label[this->labelCount + 1];
    //copy the old labels into the new array
    for (int i = 0; i < this->labelCount; i++) {
        newLabels[i] = this->labels[i];
    }
    //add the new label to the end of the array
    newLabels[this->codeSize] = {std::move(name), lineNumber};
    //delete the old labels
    delete[] this->labels;
    //set the labels to the new labels
    this->labels = newLabels;
    //increment the label count
    this->labelCount++;
}
//get a line of code
std::string Code::getLine(int lineNumber) {
    //return the line of code
    return this->code[lineNumber];
}
//get the line number of a label
int Code::getLabelLineNumber(const std::string& name) {
    //loop through the labels
    for (int i = 0; i < this->labelCount; i++) {
        //if the label name matches the name passed in
        if (this->labels[i].name == name) {
            //return the line number
            return this->labels[i].lineNumber;
        }
    }
    //if the label doesn't exist, return -1
    return -1;
}
//get the code size
int Code::getCodeSize() const {
    //return the code size
    return this->codeSize;
}
