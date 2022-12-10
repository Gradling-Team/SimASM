//
// Created by vinanddrinks on 09/12/2022.
// Copyright (c) 2022 Gradling Team. All rights reserved.

#ifndef SIMASM_MEMORY_HPP
#define SIMASM_MEMORY_HPP
#include <iostream>
#include <vector>
class Memory {
    private:
        static Memory * memoryInstance;
        struct MemoryCell {
            std::string name;
            int address;
            int data;
        };
        std::vector<MemoryCell> memory;
        int size;
        Memory();

    public:
        static Memory* getInstance();
        ~Memory();
        void store(std::string name, int data);
        void store(const std::string& name, int data, int shift);// indirect addressing
        int erase(int address);
        int erase(const std::string& name);
        int get(const std::string& name);
        int get(int address);
        int get(const std::string& name, int shift); // indirect addressing
        int getAddr(const std::string& name);
        void clear();
};


#endif //SIMASM_MEMORY_HPP