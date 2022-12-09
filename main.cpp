#include <iostream>
using namespace std;
#include "fileReader.cpp"

int main() {
    std::cout << "Hello, World!" << std::endl;
    FileReader fileReader;
    fileReader.read("example.txt");

    return 0;
}