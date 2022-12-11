//
// Created by vinanddrinks on 09/12/2022.
//

#ifndef SIMASM_SEQUENCER_HPP
#define SIMASM_SEQUENCER_HPP
#include <iostream>
#include <string>
#include "CPUdependencies/Code.hpp"
#include "FileParsing.hpp"
#include "Memory.hpp"
class Sequencer { // this class analyse the code from the text file and load the variable in the memory, and the code in the code memory
private:
    FileParsing * fileParsing;
    Code * code;
    Memory * memory;
    static int * parseArray(const std::string& line);
public:
    Sequencer(Memory * mem,Code * codeMem,FileParsing * reader);// Constructor
    ~Sequencer(); // Destructor
    void loadCode(); // Load the code in the code memory
    void loadVariables(); // Load the variables in the memory
    void loadCodeAndVariables(); // Load the code and the variables in the memory
    void loadArray(const std::string& line); // Load the arrays in the memory
    void loadVariable(std::string line);

    static int getArraySize(const std::string &line);
};


#endif //SIMASM_SEQUENCER_HPP
