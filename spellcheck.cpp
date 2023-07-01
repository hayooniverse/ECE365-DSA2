#include <iostream>
#include <ctime>
#include <fstream>
#include <cstdio>

#include "hash.h"

using namespace std;

char validChar(char c){
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
        return c;
    }
    // Valid Characters (- or ')
    else if(c==45 || c== 39){
        return c;
    }
    // Invalid Characters: word separator
    else{
        return -1;
    }
}

int numLines(ifstream& inputFile){
    int count = 0;
    string line;
    while(getline(inputFile, line)){
        count++;
    }
    return count;
}

string readInput(ifstream& inputFile){
    string word = "";
    char c = 0;
    
    while(c!=EOF){
        inputFile.get(c);
        c = validChar(c);
        if(c==-1){
            break;
        }
        word = word + c;
    }
    return word;
}

void readDict(ifstream& dictFile){
    int size = numLines(dictFile);
    hashTable dictionary(size);
    for(int i=1;i==50;i++){
        string word = readInput(dictFile);
        // dictionary.insert(word);
    }
}

int main(){

    string dictName, inputFileName, outputFileName;
    clock_t time;
    ifstream dictFile, inputFile;

    // cout<<"Enter name of dictionary: ";
    // cin>>dictName;
    dictName = "sample_dict.txt";
    dictFile.open(dictName);

    time = clock();
    /*insert dictionary loading method*/
    // string first;
    
    cout<<readInput(dictFile)<<endl;
    cout<<numLines(dictFile)<<endl;
    // time = clock() - time;

    // cout<<"Total time (in seconds) to load dictionary: " << time / CLOCKS_PER_SEC << endl;
    // cout<<"Enter name of input file: ";
    // cin>>inputFileName;    
    // cout<<"Enter name of output file: ";
    // cin>>outputFileName;

    // time = clock();
    // /*insert spell check algorithm*/
    // time = clock() - time;

    // cout<<"Total time (in seconds) to check document: " << time / CLOCKS_PER_SEC << endl;

    return 0;
}