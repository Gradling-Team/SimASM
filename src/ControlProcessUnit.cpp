//
// Created by vinanddrinks on 11/12/2022.
//

#include "ControlProcessUnit.hpp"
#include "CPUdependencies/ArithmeticLogicUnit.hpp"
#include "CPUdependencies/Code.hpp"
ControlProcessUnit::ControlProcessUnit() {
    this->memPtr = Memory::getInstance();
    this->codePtr = Code::getInstance();
    this->aluPtr = new ArithmeticLogicUnit();
    this->stepByStep = false;
}
// destructor
ControlProcessUnit::~ControlProcessUnit() {
    delete this->aluPtr;
    this->aluPtr = nullptr;
    this->memPtr = nullptr;
    this->codePtr = nullptr;
}
void ControlProcessUnit::run(bool stepByStep) {// this function represent a cpu cycle
    //get the next line of code
    // if the user wants to step through the code
    this->stepByStep = stepByStep;
    // we display an acknowledgment
    if (this->stepByStep) {
        std::cout << "You are now stepping through the code." << std::endl;
        std::cout << "Press enter to continue..." << std::endl;
        std::cin.get();
    }
    while (aluPtr->getPC() >=0) {
        std::string line = this->codePtr->getLine(aluPtr->getPC());
        //load the op code
        this->loadOpCode(line);
        // if the user wants to step through the code we display the current status
        if(stepByStep){
            std::cout << "Line: " << line << std::endl;
            std::cout << "PC: " << aluPtr->getPC() << std::endl;
            codePtr->display();
            memPtr->display();
            aluPtr->displayStatus();
            // we wait for the user to acknowledge
            std::string tmp = " ";
            while(tmp != "y" && tmp != "Y" && tmp !="n" && tmp !="N" && tmp !="\n" && tmp != "\r" && !tmp.empty()){
            std::cout << "do you want to keep step by step ? [Y/n]"<<std::endl;
            std::getline(std::cin, tmp);
            if(tmp == "y" || tmp == "Y" || tmp == "\n" || tmp == "\r" || tmp.empty()){
            continue;}
            if(tmp == "n" || tmp == "N"){
                stepByStep = false;
            }}

        }
        //execute the op code
        this->executeOpCode();
        //increment the program counter if line is not a "HLT" instruction
        if(this->currentOpCode.op != "HLT") {
            aluPtr->incPC();
        }
        if (this->aluPtr->getPC() >= this->codePtr->getCodeSize()) {
            this->aluPtr->setTMP(-1);
            this->aluPtr->LDA("PC", "TMP");
        }
    }
}

//load the op code
// the line is split into 4 parts separated by white space
// the first part is the operation
// the second part is the first argument
// the third part is the second argument
// the fourth part is the third argument
void ControlProcessUnit::loadOpCode(const std::string& line) {
    //create a string stream
    std::stringstream ss(line);
    //create a string to hold each part of the line
    std::string part;
    //get the first part of the line
    ss >> part;
    //set the operation
    this->currentOpCode.op = part;
    this->currentOpCode.argNumber = 0;
    std::string partOld = part;
    //we load the arguments in a loop
    for ( int i = 0; i < 3; i++){
        //if the part is not empty
        ss >> part;
        if (!part.empty()){
            //set the argument
            switch (i){
                case 0:
                    if(part != partOld){
                    this->currentOpCode.arg1 = part;
                    this->currentOpCode.arg1Type = ControlProcessUnit::getArgType(part);
                    break;} else {
                        this->currentOpCode.arg1 = "";
                        this->currentOpCode.arg1Type = -1;
                        this->currentOpCode.argNumber--;
                        break;
                    }
                case 1:
                    if(part != partOld){
                        this->currentOpCode.arg2 = part;
                        this->currentOpCode.arg2Type = ControlProcessUnit::getArgType(part);
                    break;} else{
                        this->currentOpCode.arg2 = "";
                        this->currentOpCode.arg2Type = -1;
                        this->currentOpCode.argNumber--;
                        break;
                    }
                case 2:
                    if(part != partOld){
                        this->currentOpCode.arg3 = part;
                        this->currentOpCode.arg3Type = ControlProcessUnit::getArgType(part);
                    break;
                    } else {
                        this->currentOpCode.arg3 = "";
                        this->currentOpCode.arg3Type = -1;
                        this->currentOpCode.argNumber--;
                        break;
                    }
                default:
                    break;
            }
            partOld = part;
            //increment the argument number
            this->currentOpCode.argNumber++;
        }
    }
}
//execute the op code
void ControlProcessUnit::executeOpCode() {
    //switch case to select and execute operation
    // if arg2 or arg3 are memory or immediate/constant we need to get the value int a TMP register
    bool arg1IsMemOrConst = this->currentOpCode.arg1Type == 1 || this->currentOpCode.arg1Type == 2;
    bool arg2IsMemOrConst = this->currentOpCode.arg2Type == 1 || this->currentOpCode.arg2Type == 2;
    //if arg1 is memory or immediate/constant we need to get the value in a TMP2 register
    if (this->currentOpCode.arg1Type == 2){
        this->aluPtr->setTMP2(std::stoi(this->currentOpCode.arg1));
    } else if (this->currentOpCode.arg1Type == 1){
        // we check if the argument is an array
        if (this->currentOpCode.arg1.find('[') != std::string::npos){
            // we get the array name
            std::string arrayName = this->currentOpCode.arg1.substr(0, this->currentOpCode.arg1.find('['));
            // we get the index
            std::string index = this->currentOpCode.arg1.substr(this->currentOpCode.arg1.find('[') + 1, this->currentOpCode.arg1.find(']') - 1);
            // we get the value in the array at the index
            this->aluPtr->setTMP2(this->memPtr->get(arrayName, std::stoi(index)));
        } else {
            // we get the value in the memory
            this->aluPtr->setTMP2(this->memPtr->get(this->currentOpCode.arg1));
        }
    }
    if(this->currentOpCode.arg2Type == 2){
        this->aluPtr->setTMP(std::stoi(this->currentOpCode.arg2));
    } else if (this->currentOpCode.arg2Type == 1){
        //we first check if the memory is an array
        if (this->currentOpCode.arg2.find('[') != std::string::npos){
            //we get the index
            int index = std::stoi(this->currentOpCode.arg2.substr(this->currentOpCode.arg2.find('[')+1, this->currentOpCode.arg2.find(']')-1));
            //we get the array name
            std::string arrayName = this->currentOpCode.arg2.substr(0, this->currentOpCode.arg2.find('['));
            //we get the value from the memory
            this->aluPtr->setTMP(this->memPtr->get(arrayName, index));
        } else {
            //we get the value from the memory
            this->aluPtr->setTMP(this->memPtr->get(this->currentOpCode.arg2));
        }
    }
    if(this->currentOpCode.arg3Type == 2){
        this->aluPtr->setTMP2(std::stoi(this->currentOpCode.arg3));
    } else if (this->currentOpCode.arg3Type == 1){
        //we first check if the memory is an array
        if (this->currentOpCode.arg3.find('[') != std::string::npos){
            //we get the index
            int index = std::stoi(this->currentOpCode.arg3.substr(this->currentOpCode.arg3.find('[')+1, this->currentOpCode.arg3.find(']')-1));
            //we get the array name
            std::string arrayName = this->currentOpCode.arg3.substr(0, this->currentOpCode.arg3.find('['));
            //we get the value from the memory
            this->aluPtr->setTMP2(this->memPtr->get(arrayName, index));
        } else {
            //we get the value from the memory
            this->aluPtr->setTMP2(this->memPtr->get(this->currentOpCode.arg3));
        }
    }
    // then we can use the TMP register as the argument
    // we need to do this because the ALU only works with registers
    // Memory load and store operations are not affected by this
        // we check first if the operation is a label line finishing with ':'
        if (this->currentOpCode.op.back() == ':'){
            return;
        }
        switch (this->currentOpCode.op[0]) {
            case 'A':
                if (this->currentOpCode.op == "ADD") { // first arg is always a register
                    if (arg2IsMemOrConst) {
                        aluPtr->ADD(this->currentOpCode.arg1, "TMP");
                    } else {
                        aluPtr->ADD(this->currentOpCode.arg1, this->currentOpCode.arg2);
                    }
                } else if (this->currentOpCode.op == "AND") {
                    if (arg2IsMemOrConst) {
                        aluPtr->AND(this->currentOpCode.arg1, "TMP");
                    } else {
                        aluPtr->AND(this->currentOpCode.arg1, this->currentOpCode.arg2);
                    }
                }
                break;
            case 'B':
                // here only arg1 and arg2 can be register or memory or immediate/constant arg3 is always a label
                if (currentOpCode.op == "BEQ") {
                    if (arg1IsMemOrConst) {
                        if (arg2IsMemOrConst) {
                            aluPtr->BEQ("TMP2", "TMP", this->currentOpCode.arg3);
                        } else {
                            aluPtr->BEQ("TMP2", this->currentOpCode.arg2, this->currentOpCode.arg3);
                        }
                    } else {
                        if (arg2IsMemOrConst) {
                            aluPtr->BEQ(this->currentOpCode.arg1, "TMP", this->currentOpCode.arg3);
                        } else {
                            aluPtr->BEQ(this->currentOpCode.arg1, this->currentOpCode.arg2, this->currentOpCode.arg3);
                        }
                    }
                } else if (currentOpCode.op == "BNE") {
                    if (arg1IsMemOrConst) {
                        if (arg2IsMemOrConst) {
                            aluPtr->BNE("TMP2", "TMP", this->currentOpCode.arg3);
                        } else {
                            aluPtr->BNE("TMP2", this->currentOpCode.arg2, this->currentOpCode.arg3);
                        }
                    } else {
                        if (arg2IsMemOrConst) {
                            aluPtr->BNE(this->currentOpCode.arg1, "TMP", this->currentOpCode.arg3);
                        } else {
                            aluPtr->BNE(this->currentOpCode.arg1, this->currentOpCode.arg2, this->currentOpCode.arg3);
                        }
                    }
                } else if (currentOpCode.op == "BBG") {
                    if (arg1IsMemOrConst) {
                        if (arg2IsMemOrConst) {
                            aluPtr->BBG("TMP2", "TMP", this->currentOpCode.arg3);
                        } else {
                            aluPtr->BBG("TMP2", this->currentOpCode.arg2, this->currentOpCode.arg3);
                        }
                    } else {
                        if (arg2IsMemOrConst) {
                            aluPtr->BBG(this->currentOpCode.arg1, "TMP", this->currentOpCode.arg3);
                        } else {
                            aluPtr->BBG(this->currentOpCode.arg1, this->currentOpCode.arg2, this->currentOpCode.arg3);
                        }
                    }
                } else if (currentOpCode.op == "BSM") {
                    if (arg1IsMemOrConst) {
                        if (arg2IsMemOrConst) {
                            aluPtr->BSM("TMP2", "TMP", this->currentOpCode.arg3);
                        } else {
                            aluPtr->BSM("TMP2", this->currentOpCode.arg2, this->currentOpCode.arg3);
                        }
                    } else {
                        if (arg2IsMemOrConst) {
                            aluPtr->BSM(this->currentOpCode.arg1, "TMP", this->currentOpCode.arg3);
                        } else {
                            aluPtr->BSM(this->currentOpCode.arg1, this->currentOpCode.arg2, this->currentOpCode.arg3);
                        }
                    }
                }
                break;
            case 'D':
                if (this->currentOpCode.op == "DIV") { // first arg is always a register
                    if (arg2IsMemOrConst) {
                        aluPtr->DIV(this->currentOpCode.arg1, "TMP");
                    } else {
                        aluPtr->DIV(this->currentOpCode.arg1, this->currentOpCode.arg2);
                    }
                } else if (this->currentOpCode.op == "DEC") {
                    aluPtr->DEC(this->currentOpCode.arg1);
                }
                break;
            case 'H':
                this->aluPtr->HLT();
                break;
            case 'I':
                aluPtr->INC(this->currentOpCode.arg1);
                break;
            case 'J':
                aluPtr->JMP(this->currentOpCode.arg1);
                break;
            case 'L':
                // arg 1 is always a register, arg 2 can be a memory location or a constant, arg 3 is always a constant and optional
                if (this->currentOpCode.op == "LDA") {
                    if (arg2IsMemOrConst) {
                        aluPtr->LDA(this->currentOpCode.arg1, "TMP");
                    } else {
                        aluPtr->LDA(this->currentOpCode.arg1, this->currentOpCode.arg2);
                    }
                } else if (this->currentOpCode.argNumber == 3){
                    aluPtr->LDA(this->currentOpCode.arg1, this->currentOpCode.arg2, this->currentOpCode.arg3);
                }
                break;
            case 'M':
                // arg 1 is always a register, arg 2 can be a memory location or a constant, no arg 3
                if (this->currentOpCode.op == "MUL") {
                    if (arg2IsMemOrConst) {
                        aluPtr->MUL(this->currentOpCode.arg1, "TMP");
                    } else {
                        aluPtr->MUL(this->currentOpCode.arg1, this->currentOpCode.arg2);
                    }
                }else if(this->currentOpCode.op == "MOD"){
                    if (arg2IsMemOrConst) {
                        aluPtr->MOD(this->currentOpCode.arg1, "TMP");
                    } else {
                        aluPtr->MOD(this->currentOpCode.arg1, this->currentOpCode.arg2);
                    }
                }
                break;
            case 'N':
                if (this->currentOpCode.op == "NOP") {
                    aluPtr->NOP();
                }else if(this->currentOpCode.op == "NOT") {
                    aluPtr->NOT(this->currentOpCode.arg1);
                }
                break;
            case 'O':
                // arg 1 is always a register, arg 2 can be a memory location or a constant, no arg 3
                if (this->currentOpCode.op == "OR") {
                    if (arg2IsMemOrConst) {
                        aluPtr->OR(this->currentOpCode.arg1, "TMP");
                    } else {
                        aluPtr->OR(this->currentOpCode.arg1, this->currentOpCode.arg2);
                    }
                }
                break;
            case 'P':
                // arg 1 can be a register a memory location or a constant, no arg2 or arg3
                if (this->currentOpCode.op == "PUSH") {
                    if (arg1IsMemOrConst) {
                        aluPtr->PUSH("TMP2");
                    } else {
                        aluPtr->PUSH(this->currentOpCode.arg1);
                    }
                } else if (this->currentOpCode.op == "POP") { // arg 1 is always a register
                    aluPtr->POP(this->currentOpCode.arg1);
                } else if (this->currentOpCode.op == "PEEK") { // arg 1 is always a register
                    aluPtr->PEEK(this->currentOpCode.arg1);
                } else if (this->currentOpCode.op == "PEEKN"){ // arg 1 is always a register, arg 2 always a constant
                    aluPtr->PEEKN(this->currentOpCode.arg1, std::stoi(this->currentOpCode.arg2));
                }
                break;
            case 'S':
                // arg 1 is always a register, arg 2 can be a memory location or a constant, no arg 3
                if (this->currentOpCode.op == "SUB") {
                    if (arg2IsMemOrConst) {
                        aluPtr->SUB(this->currentOpCode.arg1, "TMP");
                    } else {
                        aluPtr->SUB(this->currentOpCode.arg1, this->currentOpCode.arg2);
                    }
                }else if(this->currentOpCode.op == "STR") { // arg 1 is fill as is, arg 2 is a register or a constant, arg 3 is always a constant and optional
                    if (arg2IsMemOrConst && currentOpCode.argNumber == 2) {
                        aluPtr->STR(this->currentOpCode.arg1, "TMP");
                    } else if (currentOpCode.argNumber == 2) {
                        aluPtr->STR(this->currentOpCode.arg1, this->currentOpCode.arg2);
                    }
                    if(arg2IsMemOrConst && currentOpCode.argNumber == 3){
                        aluPtr->STR(this->currentOpCode.arg1, "TMP", this->currentOpCode.arg3);
                    } else if(currentOpCode.argNumber == 3){
                        aluPtr->STR(this->currentOpCode.arg1, this->currentOpCode.arg2, this->currentOpCode.arg3);
                    }
                } else if (this->currentOpCode.op == "SRL"){
                    // arg 1 is always a register, arg 2 is a constant, no arg 3
                    aluPtr->SRL(this->currentOpCode.arg1, std::stoi(this->currentOpCode.arg2));
                } else if (this->currentOpCode.op == "SRR"){
                    // arg 1 is always a register, arg 2 is a constant, no arg 3
                    aluPtr->SRR(this->currentOpCode.arg1, std::stoi(this->currentOpCode.arg2));
                }
                break;
            default:
                break;
    }

}
//get the argument type
// 0 if registered, 1 if memory, 2 if immediate/constant
// a register start by T, a memory variable start by a letter, an immediate/constant start by a number
int ControlProcessUnit::getArgType(const std::string& arg) {
    //if the argument is a register
    if (arg[0] == 'T'){
        return 0;
    }
    //if the argument is a memory variable
    if (arg[0] >= 'a' && arg[0] <= 'z' || arg[0] >= 'A' && arg[0] <= 'Z'){
        return 1;
    }
    //if the argument is an immediate/constant
    if (arg[0] >= '0' && arg[0] <= '9'){
        return 2;
    }
    //if the argument is not a register, a memory variable or an immediate/constant
    return -1;
}