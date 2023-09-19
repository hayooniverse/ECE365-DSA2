#include <iostream>
#include <ctime>
#include <fstream>
#include <cstdio>

#include "hash.h"

using namespace std;

char validChar(char c, bool& numFlag){
    // Valid Characters (Lowercase)
    if(c>=97 && c<=122){
        return c;
    }
    // Valid Characters (Uppercase)
    else if(c>=65 && c<=90){
        return c+32;
    }
    // Valid Characters (0-9)
    else if(c>=48 && c<=57){
        numFlag = true;
        return c;
    }
    // Valid Characters (- or ')
    else if(c==45 || c== 39){
        return c;
    }
    else if(c=='\n'){
        return -2;
    }
    // Invalid Characters: word separator
    else{
        return -1;
    }
}
void loadDictionary(string& dictName, hashTable& dictionary){
    ifstream dictFile(dictName);

    if(dictFile.is_open()){
        string word = "";
        bool numFlag = false;
        char c;

        while(dictFile.get(c)){
            c = validChar(c, numFlag);
            if(c==-1 || c==-2){
                if(!word.empty() && dictionary.insert(word) == 2){
                    std::cout << "Rehash failed." << std::endl;
                    exit(EXIT_FAILURE);
                }
                word.clear();
            } else {
                word += c;
            }

            // Process the last word in the dictionary
            if(dictFile.peek() == EOF && !word.empty()){
                if(dictionary.insert(word) == 2){
                    std::cout << "Rehash failed." << std::endl;
                    exit(EXIT_FAILURE);
                }
            }
        }

        dictFile.close();
    } else {
        std::cout << "Failed to load dictionary." << std::endl;
    }
}

void spellcheck(string& inputFileName, string& outputFileName, hashTable& dictionary){
    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFileName);
    
    int count = 1;
    char c;
    string word = "";
    bool numFlag = false;

    while(inputFile.get(c)){
        c = validChar(c, numFlag);
        if(c==-1 || c==-2){
            if(!word.empty() && !numFlag){
                if(word.size() > 20){
                    outputFile << "Long word at line " << count << ", starts: " << word.substr(0,20) << endl;
                } else if(!dictionary.contains(word)){
                    outputFile << "Unknown word at line " << count << ": " << word << endl;
                }
            }
            word.clear();
            numFlag = false;
            if(c==-2){
                count++;
            }
        } else {
            word += c;
        }

        // Process the last word in the input
        if(inputFile.peek() == EOF && !word.empty() && !numFlag){
            if(word.size() > 20){
                outputFile << "Long word at line " << count << ", starts: " << word.substr(0,20) << endl;
            } else if(!dictionary.contains(word)){
                outputFile << "Unknown word at line " << count << ": " << word << endl;
            }
        }
    }

    inputFile.close();
    outputFile.close();
}


int main(){
    string dictName, inputFileName, outputFileName;
    clock_t t1, t2;
    double timeTaken;

    cout<<"Enter name of dictionary: ";
    cin>>dictName;
    // dictName = "sample_dict.txt";
    // inputFileName = "lyrics.txt";
    // outputFileName = "output.txt";  

    t1 = clock();    
    hashTable dictionary(50000);
    loadDictionary(dictName, dictionary);
    t2 = clock();
    timeTaken = ((double)(t2 - t1)) / CLOCKS_PER_SEC;
    std::cout<<"Total time (in seconds) to load dictionary: " << timeTaken << endl;
    cout<<"Enter name of input file: ";
    cin>>inputFileName;
    
    cout<<"Enter name of output file: ";
    cin>>outputFileName;


    t1 = clock();
    spellcheck(inputFileName, outputFileName, dictionary);
    t2 = clock();
    timeTaken = ((double)(t2 - t1)) / CLOCKS_PER_SEC;

    std::cout<<"Total time (in seconds) to check document: " << timeTaken << endl;

    return 0;
}