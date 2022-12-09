//Header creation test and file reading
#ifndef SIMASM_FILEPARSING_H
#define SIMASM_FILEPARSING_H

class FileParsing
{
public:
    void read(string fileName);
    string parseWord(string line);
};

#endif //SIMASM_FILEPARSING_H
