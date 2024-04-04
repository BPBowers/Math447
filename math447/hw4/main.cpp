#include "crypto.h"
#include <iostream>
#include <cstdio>
#include <string>

int main()
{
    homework4 crypto;
    //Chapter 3 Question #1.1
    printf("--------------CHAPTER #3 COMPUTER PROBLEMS--------------\n");
    vector<InfInt> ex11 = crypto.myGCDex(17, 101);
    cout << "Answer for Chapter 3 Question #1.1: x = " << *ex11.begin() << " y = " << *(ex11.begin()+1) << endl;

    //Chapter 3 Question #1.2
    InfInt ex12 = crypto.myModInverse(17, 101);
    cout << "Answer for Chapter 3 Question #1.2: " << ex12 << endl;

    //Chapter 3 Question #2.2
    InfInt ex221 = crypto.myPowMod(2, 2, 3);
    InfInt ex222 = crypto.myPowMod(2, 232, 3);
    InfInt ex223 = crypto.myPowMod(2, 333, 3);
    ex223 = crypto.myMod(ex223+1, 3);
    cout << "Answer for Chapter 3 Question #2.2:\n2^2 (mod 3) = " << ex221 << endl;
    cout << "2^232 (mod 3) = " << ex222 << endl;
    cout << "(2^233) + 1 (mod 3) = " << ex223 << endl;

    //Chapter 3 Question #4
    vector<InfInt> ex41 = crypto.myGCDex(5, 2);
    InfInt ex411 = (((InfInt)5) * *(ex41.begin())) + (((InfInt)2) * *(ex41.begin()+1));
    ex411 = crypto.myMod(ex411, 31);
    vector<InfInt> ex42 = crypto.myGCDex(3, -7);
    InfInt ex421 = (((InfInt)3) * *(ex42.begin())) + (((InfInt)-7) * *(ex42.begin()+1));
    ex421 = crypto.myMod(ex421, 31);
    cout << "Answer for Chapter 3 Question #4: " << ex411 << " is congruent with " << ex421 << " (mod 31) [Obviously this is incorrect]" << endl;

    //Chapter 3 Question #8
    InfInt ex8 = crypto.myGCD(12345678987654321, 100);
    cout << "Answer for Chapter 3 Question #8: " << ex8 << endl;

    printf("\n--------------OTHER TEST CODE--------------\n\n");
    InfInt j = crypto.myMod(-17, 90);
    cout << "mod(-17, 90) = " << j << endl;
    InfInt gcd = crypto.myGCD(52, 12);
    cout << "gcd(52, 12) = " << gcd << endl;
    
    InfInt x = crypto.myGCD(45621, 12554);
    std::cout<< "GCD(45621, 12554) = " << x << std::endl;

    vector<InfInt> resVec = crypto.myGCDex(1097, 17);
    printf("Extended GCD function for gcdex(a,b) = ");
    for (auto a = resVec.begin(); a < resVec.end(); a++)
        cout << *a << " "; 
    printf("\n");
    
    InfInt pow = crypto.myPowMod(56, 4777, 477);
    cout << "power_mod(56, 4777, 477) = " <<pow << endl;//In-Class example

    InfInt inverse = crypto.myModInverse(7, 17);
    cout << "modinverse(7, 17) = " << inverse << endl;

    InfInt chinese = crypto.myChinese(8, 21, 9, 16);
    cout << "Non General Chinese Remainder Theorem: crt(8, 21, 9, 16) = " << chinese << endl;

    //cout << "Start of program" << endl;
    
    vector<InfInt> aVec;
    aVec.push_back(1);
    
    aVec.push_back(-1);
    aVec.push_back(1);
    
    vector<InfInt> mVec;
    mVec.push_back(11);
    mVec.push_back(13);
    mVec.push_back(17);
    
    InfInt GenChinese = crypto.myGenChinese(aVec, mVec);
    cout << "Generalized Chinese Remainder: crt([1, -1, 1], [11, 13, 17]) = " << GenChinese << endl;
    return 0;
}