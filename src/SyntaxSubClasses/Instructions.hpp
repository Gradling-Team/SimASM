//
// Created by mathieu on 10/12/22.
//

#ifndef SIMASM_INSTRUCTIONS_HPP
#define SIMASM_INSTRUCTIONS_HPP

#include <string>
enum argType {NO, REG, VAR, VC, RC, RVC, LABEL};

class Instructions {
private:
    std::string name;
    argType type[3];


public:
    // Constructor
    explicit Instructions(std::string, argType, argType, argType);
    // Destructor
    ~Instructions();
    // Methods
    // Getters
    //Definition of argument types as an enum
// 0 = no argument, 1 = register, 2 = variable,  3 = var/const, 4 = reg/const 5 = reg/var/const, 6 = label

};


#endif //SIMASM_INSTRUCTIONS_HPP
