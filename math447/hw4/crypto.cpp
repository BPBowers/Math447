
/*
#include "crypto.h"

int homework4::myMod(int a, int n)
{
    int tempA = a;
    if (a < 0)
        tempA = n + a;
    else
        tempA = a;
    while(tempA - n > n){
        tempA -= n;
    }
    return tempA;
}

int homework4::myGCD(int a, int n)
{
    //a = x * n + b
    int tempA, tempX, tempN, tempB, b, x;
    while(true){
        tempX = tempA/tempN;
        tempB = tempA - (tempX * tempN);
        if (tempB == 0)
            break;
        else{
            tempA = tempN;
            b = tempB;
            x = tempX;
            tempN = tempB;
        }
    }
    return b;//Returns second to 
}

int homework4::myModInverse(int a, int n)
{
    int number;
    return number;
}
*/