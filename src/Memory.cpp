//
// Created by vinanddrinks on 09/12/2022.
// Copyright (c) 2022 Gradling Team. All rights reserved.
#include "Memory.hpp"
#include <iostream>
#include <utility>
// instance definition
Memory * Memory::memoryInstance = nullptr;
//constructor
Memory::Memory() {
    this->memory.clear();
    this->memory.resize(0x10000);
    this->size = 0;
}
//destructor
Memory::~Memory() {
    delete this->memory.data();
    this->size = 0;
}
//methods
void Memory::store(std::string name, int data) {
    size++;
    MemoryCell cell;
    cell.name = std::move(name);
    cell.address = size;
    cell.data = data;
    memory.push_back(cell);
}
void Memory::store(const std::string& name, int data, int shift) {
    int address = getAddr(name);
    address += shift;
    if(address >= 0x10000) {
        std::cout << "Error: Address out of bounds" << std::endl;
        return;
    }
    if(address >= size) {
        store(name, data);
    }else {
        memory[address].data = data;
    }
}
int Memory::erase(const std::string& name) {
    int data = 0;
    for (const auto &i : memory) {
        if (i.name == name) {
            data = i.data;
            memory.erase(memory.begin() + i.address);
            size--;
            break;
        }
    }
    return data;
}
int Memory::erase(int address) {
    int data = 0;
    for (const auto &i : memory) {
        if (i.address == address) {
            data = i.data;
            memory.erase(memory.begin() + i.address);
            size--;
            break;
        }
    }
    return data;
}
//getters
int Memory::get(int address) {
    for (const auto &i : memory) {
        if (i.address == address) {
            return i.data;
        }
    }
return 0;
}
int Memory::get(const std::string& name) {
    for (const auto &i : memory) {
        if (i.name == name) {
            return i.data;
        }
    }
    return 0;
}
int Memory::get(const std::string& name, int shift) {
    int address = getAddr(name);
    address += shift;
    if(address >= 0x10000) {
        std::cout << "Error: Address out of bounds" << std::endl;
        return 0;
    }
    if(address >= size) {
        return 0;
    }else {
        return memory[address].data;
    }
}
int Memory::getAddr(const std::string &name) {
    for (const auto &i : memory) {
        if (i.name == name) {
            return i.address;
        }
    }
    return 0;
}
//clear
void Memory::clear() {
    delete this->memory.data();
    this->memory.clear();
    this->memory.resize(0x10000);
    this->size = 0;
}
//get instance
Memory* Memory::getInstance() {
    if (Memory::memoryInstance == nullptr) {
        Memory::memoryInstance = new Memory();
    }
    return Memory::memoryInstance;
}