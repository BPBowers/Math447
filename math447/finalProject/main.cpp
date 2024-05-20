//Brian Bowers | Math-447
//Final Project | Book Cipher Randomness Tester
#include <iostream>
#include <fstream>//File stream
#include "knuth.h"

using namespace std;

int main(){
    //First Version we just gonna open Beale Ciphertext 2
    KnuthFunc knuth;
    string filename;
    while(true){
        printf("Please enter the file-name and/or path you want the signature of:\n");
        cin >> filename;
        ifstream cipherText(filename);
        string outFile = "signatures/signature-";
        std::size_t pos = filename.find_last_of('/');
        pos++;
        outFile += filename.substr(pos);
        //outFile += ".txt";
        ofstream signature(outFile);
        knuth.testValidity(cipherText, signature);
        printf("Do you wish to perform another signature capture? Enter y to do so:\n");
        char answer;
        cin >> answer;
        if (answer == 'y')
            continue;
        else
        {
            printf("Goodbye!\n");
            break;
        }
    }
}