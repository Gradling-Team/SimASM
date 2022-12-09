//Header creation test and file reading
#ifndef SIMASM_FILEPARSING_H
#define SIMASM_FILEPARSING_H
using namespace std;
class FileParsing
{
public:
    void read(std::string fileName);
    std::string parseWord(std::string line);
};

#endif //SIMASM_FILEPARSING_H
