//
// Created by vinanddrinks on 09/12/2022.
//

#include "Sequencer.hpp"
#include <iostream>
#include <utility>
#include <sstream>
// Constructor
Sequencer::Sequencer(Memory *mem, Code *codeMem, FileParsing *reader) {
    this->fileParsing = reader;
    this->code = codeMem;
    this->memory = mem;
}
// Destructor
Sequencer::~Sequencer() {
    delete this->fileParsing;
}

// Load the code in the code memory
// executable code start after the line that contains the word "#code"
void Sequencer::loadCode(){
    this->fileParsing->cleanFStream();
    std::string line;
    // navigate to the code section
    while (line != "#code"){
        line = this->fileParsing->getLine();
    }
    // load the code
    while (!line.empty()){
        line = this->fileParsing->getLine();
        if (!line.empty()){
            this->code->add(line);
        }
    }
}

// Load a variable in the memory
void Sequencer::loadVariable(std::string line){
    std::string name;
    int value;
    std::stringstream ss(line);
    ss >> name >> value;
    this->memory->store(name,value);
}
// Load the variables in the memory
// variables can be declared lazily using "?" instead of a value or with a value
// if a variable is declared with a value, it is stored in the memory
// if a variable is declared lazily, it is stored in the memory with the value 0
// if there is a [ or , in the line, it is an array, and it is loaded with the loadArray() method
int * Sequencer::parseArray(const std::string& line){
    int * array = new int[100];
    std::string name;
    int value;
    std::stringstream ss(line);
    ss >> name >> value;
    array[0] = value;
    int i = 1;
    while (ss >> value){
        array[i] = value;
        i++;
    }
    return array;
}
int Sequencer::getArraySize(const std::string& line){
    int size = 0;
    std::string name;
    int value;
    std::stringstream ss(line);
    ss >> name >> value;
    size++;
    while (ss >> value){
        size++;
    }
    return size;
}
void Sequencer::loadArray(const std::string& line){
    int * array = parseArray(line);
    std::string name;
    std::stringstream ss(line);
    ss >> name;
    this->memory->storeArray(name,array,getArraySize(line));

}
// now we can load all the "#data" section in the memory
void Sequencer::loadVariables(){
    this->fileParsing->cleanFStream();
    std::string line;
    // navigate to the data section
    while (line != "#data"){
        line = this->fileParsing->getLine();
    }
    // load the variables
    while (!line.empty()){
        line = this->fileParsing->getLine();
        if (!line.empty()){
            if (line.find("[") != std::string::npos || line.find(",") != std::string::npos){
                loadArray(line);
            } else {
                loadVariable(line);
            }
        }
    }
}