//
// Created by mathieu on 10/12/22.
//

#include "Instructions.hpp"

#include <utility>

Instructions::Instructions(std::string name, argType arg1, argType arg2, argType arg3){
    this->name = std::move(name);
    this->type[0] = arg1;
    this->type[1] = arg2;
    this->type[2] = arg3;
}

Instructions::~Instructions() = default;
