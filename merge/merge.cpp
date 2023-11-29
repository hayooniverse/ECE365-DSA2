// Hailey Hayoon Chung

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Iniitialize the 2D bool matrix
bool dp[1001][1001];

// Function to determine if string C is a merge of string A and string B
bool isMerge(const string& A, const string& B, const string& C) {

    // if the lengths don't match -> not a merge
    if (C.length() != A.length() + B.length()) {
        return false;
    }
    // A for-loop to fill in the bool dp matrix
    for (int i = 0; i <= A.length(); i++) {
        for (int j = 0; j <= B.length(); j++) {
            // dp[0][0] is always true
            if (i == 0 && j == 0) {
                dp[i][j] = true;
            } 
            // Return true if the letter from A matches the letter from C and a merge was possible until the previous letter
            else if (i > 0 && A[i-1] == C[i+j-1] && dp[i-1][j]) {
                dp[i][j] = true;
            } 
            // Return true if the letter from B matches the letter from C and a merge was possible until the previous letter
            else if (j > 0 && B[j-1] == C[i+j-1] && dp[i][j-1]) {
                dp[i][j] = true;
            } 
            // Return false if none of the above are possible
            else {
                dp[i][j] = false;
            }
        }
    }
    // Return merge results for strings A and B into string C
    return dp[A.length()][B.length()];
}

// Function for capitalizing letters from A if a merge is possible
string merge(const string& A, const string& B, const string& C) {
    
    // Print output when a merge is not possible
    if (!isMerge(A, B, C)) {
        return "*** NOT A MERGE ***";
    }
    else {
        string result(C.length(), ' ');
        int i = A.size(), j = B.size();

        // A while loop to iterate backwards until all letters from A and B are used
        while (i > 0 || j > 0) {
            // Prioritizing letter B since iterating backwards, check if merge is possible after taking the letter
            if (j > 0 && dp[i][j-1]) {
                result[i+j-1] = C[i+j-1];
                j--;
            } 
            // Capitalize letters from string A
            else {
                result[i+j-1] = toupper(C[i+j-1]);
                i--;
            }
        }
        return result;
    }
}

int main() {
    string inputFileName, outputFileName;
    cout << "Enter name of input file: ";
    cin >> inputFileName;
    cout << "Enter name of output file: ";
    cin >> outputFileName;

    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFileName);

    string A, B, C;
    while (getline(inputFile, A) && getline(inputFile, B) && getline(inputFile, C)) {
        string merged = merge(A, B, C);
        outputFile << merged << endl;
    }

    inputFile.close();
    outputFile.close();
    return 0;
}
