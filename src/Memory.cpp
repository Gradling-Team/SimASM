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
    this->size = 0;
}
//destructor
Memory::~Memory() {
    delete this->memory.data();
    this->size = 0;
}
//methods
void Memory::store(std::string name, int data) {
    // check if the name is already in the memory
    for (int i = 0; i < this->size; i++) {
        if (this->memory.at(i).name == name) {
            // if it is, update the data
            this->memory.at(i).data = data;
            return;
        }
    }
    // if it isn't, add it to the memory
    // check if the memory is full
    if (this->size == 10000) {
        // if it is, throw an error
        throw std::runtime_error("Memory is full");
    }
    MemoryCell cell;
    cell.name = std::move(name);
    cell.address = size;
    cell.data = data;
    memory.push_back(cell);
    size++;
}
void Memory::store(const std::string& name, int data, int shift) {
    int address = getAddr(name);
    address += shift;
    if(address >= 10000) {
        std::cout << "Error: memory is full" << std::endl;
        return;
    }
    if(address >= size) {
        store(name, data);
    }else {
        memory.at(address).data = data;
    }
}
int Memory::erase(const std::string& name) {
    int data = 0;
    for (int i = 0; i < this->size; i++) {
        if (this->memory.at(i).name == name) {
            data = this->memory.at(i).data;
            this->memory.erase(this->memory.begin() + i);
            this->size--;
            return data;
        }
    }
    return data;
}
int Memory::erase(int address) {
    int data = 0;
    for (int i = 0; i < this->size; i++) {
        if (this->memory.at(i).address == address) {
            data = this->memory.at(i).data;
            this->memory.erase(this->memory.begin() + i);
            this->size--;
            return data;
        }
    }
    return data;
}
void Memory::storeArray(const std::string& name, int ** data, int length) {
    for (int i = 0; i < length; i++) {
        store(name, data[i][0], i);
    }
}
//getters
int Memory::get(int address) {
    for (int i = 0; i < this->size; i++) {
        if (this->memory.at(i).address == address) {
            return this->memory.at(i).data;
        }
    }
return 0;
}
int Memory::get(const std::string& name) {
    for (int i = 0; i < this->size; i++) {
        if (this->memory.at(i).name == name) {
            return this->memory.at(i).data;
        }
    }
    return 0;
}
int Memory::get(const std::string& name, int shift) {
    int address = getAddr(name);
    address += shift;
    if(address >= 10000) {
        std::cout << "Error: Address out of bounds" << std::endl;
        return 0;
    }
    if(address >= size) {
        return 0;
    }else {
        return memory.at(address).data;
    }
}
int Memory::getAddr(const std::string &name) {
    for (int i = 0; i < this->size; i++) {
        if (this->memory.at(i).name == name) {
            return this->memory.at(i).address;
        }
    }
    return 0;
}
int Memory::getCurrentSize() const {
    return size;
}
Memory::MemoryCell Memory::getCell(const std::string& name) {
    for (int i = 0; i < this->size; i++) {
        if (this->memory.at(i).name == name) {
            return this->memory.at(i);
        }
    }
    // if not found return empty cell
    MemoryCell cell;
    cell.name = "null";
    cell.address = 0;
    cell.data = 0;
    return cell;
}
Memory::MemoryCell Memory::getCell(int address) {
    for (int i = 0; i < this->size; i++) {
        if (this->memory.at(i).address == address) {
            return this->memory.at(i);
        }
    }
    // if not found return empty cell
    MemoryCell cell;
    cell.name = "null";
    cell.address = 0;
    cell.data = 0;
    return cell;
}
//clear
void Memory::clear() {
    delete this->memory.data();
    this->memory.clear();
    this->size = 0;
}
//get instance
Memory* Memory::getInstance() {
    if (Memory::memoryInstance == nullptr) {
        Memory::memoryInstance = new Memory();
    }
    return Memory::memoryInstance;
}