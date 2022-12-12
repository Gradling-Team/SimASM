//
// Created by vinanddrinks on 09/12/2022.
//

#ifndef SIMASM_CODE_HPP
#define SIMASM_CODE_HPP
#include <string>
#include <vector>
class Code {// singleton class to store executable assembly code
private:
    static Code *instancePtr;
    Code();

    std::string *code;
    int codeSize;
    int labelCount;
    struct Label {
        std::string name;
        int lineNumber;
    };
    std::vector<Label> labels;
     // friend function to print the code
public:
    static Code* getInstance();
    void add(std::string line);
    void addLabel(std::string name, int lineNumber);
    void clear();
    std::string getLine(int lineNumber);
    int getLabelLineNumber(const std::string& name);
    int getCodeSize() const;
    friend std::ostream &operator<<(std::ostream &os, const Code &code);
    void display() const;
    ~Code();
};


#endif //SIMASM_CODE_HPP
