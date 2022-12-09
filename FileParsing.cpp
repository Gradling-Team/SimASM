//Class creation test and file reading

#include <iostream>
#include <fstream>
#include "FileParsing.h"

using namespace std;

void FileParsing::read(string fileName){
    // Create a text string, which is used to output the text file
    string myText;
    // Read from the text file
    ifstream MyReadFile(fileName);
    // Use a while loop together with the getline() function to read the file line by line
    while (getline (MyReadFile, myText)) {
        // Output the text from the file

        if (!myText.find('!')){
            continue;
        }
        cout << myText << endl;
    }
    // Close the file
    MyReadFile.close();
}
string FileParsing::parseWord(string line){
    string word;
    for(char i : line){
        if(i == ' '){
            break;
        }
        word += i;
    }
    return word;
}
