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
        friend std::ostream &operator<<(std::ostream &os, const Memory &memory); // friend function to print the memory
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
        // get memory cell
        MemoryCell getCell(const std::string& name);
        MemoryCell getCell(int address);
        int getCurrentSize() const;
        int getAddr(const std::string& name);
        void storeArray(const std::string& name, int ** data, int length);
        void clear();
        void display();
};


#endif //SIMASM;_MEMORY_HPP
