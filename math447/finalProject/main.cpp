//Brian Bowers | Math-447
//Final Project | Book Cipher Randomness Tester
#include <iostream>
#include <fstream>//File stream
#include "knuth.h"

using namespace std;

int main(){
    //First Version we just gonna open Beale Ciphertext 2
    ifstream cipherText("CipherTexts/BealeC2.txt");
    KnuthFunc knuth;
    knuth.testValidity(cipherText);
    
    printf("---------------\n");
    ifstream c1("CipherTexts/BealeC1.txt");
    knuth.testValidity(c1);
    printf("---------------\n");
    ifstream c3("CipherTexts/BealeC3.txt");
    knuth.testValidity(c3);
    //First test, run test
    
}

