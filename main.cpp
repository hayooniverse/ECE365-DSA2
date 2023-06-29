#include <iostream>
#include <ctime>
#include <fstream>

using namespace std;

void readDict(ifstream& dictFile){
    
}

void readInput(ifstream& inputFile){

}

int main(){

    string dictName, inputFileName, outputFileName;
    clock_t time;
    ifstream dictFile, inputFile;

    cout<<"Enter name of dictionary: ";
    cin>>dictName;
    dictFile.open(dictName);

    time = clock();
    /*insert dictionary loading method*/
    time = clock() - time;

    cout<<"Total time (in seconds) to load dictionary: " << time / CLOCKS_PER_SEC << endl;
    cout<<"Enter name of input file: ";
    cin>>inputFileName;    
    cout<<"Enter name of output file: ";
    cin>>outputFileName;

    time = clock();
    /*insert spell check algorithm*/
    time = clock() - time;

    cout<<"Total time (in seconds) to check document: " << time / CLOCKS_PER_SEC << endl;

    return 0;
}