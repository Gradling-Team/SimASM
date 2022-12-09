#include <iostream>
using namespace std;
#include "FileParsing.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    FileParsing fileParsing;
    fileParsing.read("ASMFiles/example.txt");

    return 0;
}