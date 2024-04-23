#include "crypto.h"
#include <iostream>
#include <cstdio>
#include <string>

int main()
{
    //P-1 and Pollard Rho for Homework 9 Examples, takes a WHILE for the last ones, probably b.c. of myGCD and myMod are not optmized
    homework4 crypto;
    InfInt q1 = crypto.pMinusOne(6356214911);
    cout << "P-1 Result of 6356214911 is " << q1 << endl;

    InfInt Q1 = crypto.pollardRho(6356214911);
    cout << "Pollard Rho Result of 6356214911 is " << Q1 << endl;
  
    InfInt q2 = crypto.pMinusOne(618240007109027021);
    cout << "P-1 Result of 618240007109027021 is " << q2 << endl;

    InfInt Q2 = crypto.pollardRho(618240007109027021);
    cout << "Pollard Rho Result of 618240007109027021 is " << Q2 << endl;

    InfInt g3 = "8834884587090814646372459890377418962766907";
    InfInt q3 = crypto.pMinusOne(g3);
    cout << "P-1 Result of 8834884587090814646372459890377418962766907 is " << q3 << endl;

    InfInt Q3 = crypto.pollardRho(g3);
    cout << "P-1 Result of 8834884587090814646372459890377418962766907 is " << Q3 << endl;

    InfInt g4 = "1097986087741738453770573312625841";
    InfInt q4 = crypto.pMinusOne(g4);
    cout << "P-1 Result of 1097986087741738453770573312625841 is " << q4 << endl;

    InfInt Q4 = crypto.pollardRho(g4);
    cout << "Pollard Rho Result of 1097986087741738453770573312625841 is " << Q4 << endl;

    InfInt g5 = "6390453678534285246231992337771543242977";
    InfInt q5 = crypto.pMinusOne(g5);
    cout << "P-1 Result of 6390453678534285246231992337771543242977 is " << q5 << endl;

    InfInt Q5 = crypto.pollardRho(g5);
    cout << "Pollard Rho Result of 6390453678534285246231992337771543242977 is " << Q5 << endl;

    return 0;
}