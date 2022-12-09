#include <iostream>
using namespace std;
#include "FileParsing.cpp"

int main() {
    std::cout << "Hello, World!" << std::endl;
    FileParsing fileParsing;
    fileParsing.read("example.txt");

    return 0;
}