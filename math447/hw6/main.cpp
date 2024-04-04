#include "crypto.h"
#include <iostream>
#include <cstdio>
#include <string>

int main()
{
    homework4 crypto;
    printf("--------------CHAPTER #3 COMPUTER PROBLEMS--------------\n");
    cout << "ANSWER for Chapter 3 Computer Question #6: x = ";
    if(crypto.myGCD(314, 11111) == 1)
    {
        InfInt modInv = crypto.myModInverse(314, 11111);
        InfInt chap3q6 = crypto.myMod(modInv * 271, 11111);
        cout << chap3q6 << endl;
    }
    else
        cout << "[a is not coprime to n, no solution to x!]"<< endl;
    
    cout << "Answer for Chapter 3 Computer Question #7: x = ";
    if(crypto.myGCD(216, 606) == 1)
    {
        InfInt modInv = crypto.myModInverse(216, 606);
        InfInt chap3q7 = crypto.myMod(modInv * 66, 606);
        cout << chap3q7 << endl;
    }
    else
        cout << "[a is not coprime to n, no solution to x!]"<< endl;

    cout << "Sqaure roots for Chapter 3 Computer Question #12: ";
    vector <InfInt> q12 = crypto.sqaureRootMod(26055, 34807);
    //vector <InfInt> q12 = crypto.sqaureRootMod(7, 23);
    for(auto i = q12.begin(); i < q12.end(); i++)
        cout << *i << " "; 
    printf("\n");
    
    cout << "Sqaure roots for Chapter 3 Computer Question #13: ";
    vector <InfInt> q13 = crypto.sqaureRootMod(1522756, 2325781);
    for(auto i = q13.begin(); i < q13.end(); i++)
        cout << *i << " "; 
    printf("(Because it returned -1, 2325781 is not congruent to 3 (mod 4) and therefore has no square roots!!)\n");
    

    printf("--------------Random Function Tests--------------\n");
    bool Fermat = crypto.femat(29);
    cout << "The Fermat Primality Test on 29 returned ";
    if (Fermat)
        cout << "True!" << endl;
    else
        cout << "False!" << endl;
    InfInt ferris = crypto.eulerPhi(209);
    cout << "The Euler Phi algorithm for 209 returned " << ferris << endl;
    bool isPrim = crypto.primRoot(6, 11);
    cout << "The Primitive Root Test for 6 mod 11 returned ";
    if (isPrim)
        cout << "True!" << endl;
    else
        cout << "False!" << endl;
    InfInt legend = crypto.legendreSym(3, 23);
    cout << "The Legendre Symbol of (3/23) is = " << legend << endl;
    InfInt jacob = crypto.jacobiSym(4321, 27945);
    cout << "The Jacobi Symbol of (4321/27945) is = " << jacob << endl;
    vector <double> contFrac = crypto.contFrac((sqrt(5)), 10);
    cout << "[Double] a_i's in the Continued fraction for sqrt(5) in 10 iterations are: ";
    for(auto i = contFrac.begin(); i < contFrac.end(); i++)
        cout << *i << " "; 
    printf("\n");
    vector <InfInt> ratFrac = crypto.ratContFrac(25, 11);
    cout << "[Rational] a_i's in the Continued fraction for 7/17 in 100 iterations are: ";
    for(auto i = ratFrac.begin(); i < ratFrac.end(); i++)
        cout << *i << " "; 
    printf("\n");
    /*
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
    */
    return 0;
}