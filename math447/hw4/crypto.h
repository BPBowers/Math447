#ifndef CRYPTO_H_INCLUDED
#define CRYPTO_H_INCLUDED

#include <iostream>
#include <vector>
#include <cmath>
#include "InfInt.h"
using namespace std;

class homework4 
{
    private:

    public:
        InfInt myMod(InfInt a, InfInt n)
        {
            InfInt tempA = a;
            if (a < 0)
                a = n + a;
            while(a >= n)
            {
                a -= n;
                //std::cout<<a<<std::endl;
            }
            //std::cout<<a<<std::endl;
            return a;
        }

        InfInt myGCD(InfInt a, InfInt n)
        {
            //a = x * n + b
            InfInt tempA, tempX, tempN, tempB, b, x;
            tempA = a;
            tempN = n;
            b = n;
            while(true){
                tempX = tempA/tempN;
                tempB = tempA - (tempX * tempN);
                //std::cout<<tempA<<" = "<<tempX<<" * "<<tempN<<" + "<<tempB<<std::endl;
                if (tempB == 0)
                    break;
                else
                {
                    tempA = tempN;
                    b = tempB;
                    x = tempX;
                    tempN = tempB;
                }
            }
            return b;//Returns second to 
        }

        vector<InfInt> myGCDex(InfInt a, InfInt n)
        {
            //a = x * n + b
            InfInt tempA, tempX, tempN, tempB, b, x;
            vector<InfInt> vecA, vecX, vecN, vecB;
            int counter = 0;
            tempA = a;
            tempN = n;
            b = n;
            while(true){
                tempX = tempA/tempN;
                tempB = tempA - (tempX * tempN);
                //std::cout<<tempA<<" = "<<tempX<<" * "<<tempN<<" + "<<tempB<<std::endl;
                if (tempB == 0)
                    break;
                else
                {
                    vecA.push_back(tempA);
                    vecB.push_back(tempB);
                    vecX.push_back(tempX);
                    vecN.push_back(tempN);
                    tempA = tempN;
                    b = tempB;
                    x = tempX;
                    tempN = tempB;
                    counter++;
                }
            }
            //b = a - x * n
            auto xi = vecX.begin();
            vector<InfInt> sVec, tVec;
            //Initialize the first two rows for s && t
            sVec.push_back(1);
            sVec.push_back(0);
            tVec.push_back(0);
            tVec.push_back(1);
            auto finS2 = sVec.begin();
            auto finS1 = sVec.begin();
            ++finS1;//This one is one ahead of the other
            auto finSCur = sVec.begin();
            finSCur += 2;//Current Position pointer, what S is being set equal to
            auto finT2 = tVec.begin();
            auto finT1 = tVec.begin();
            ++finT1;//This one is one ahead of the other
            auto finTCur = tVec.begin();
            finTCur += 2;//Current Position pointer, what T is being set equal to
            InfInt s = 0;
            InfInt t = 0;
            for(int i = 0; i < counter; i++)
            {
                //Extended Euclidean Algorithm
                s = (*finS2) + (-(*xi) * (*finS1));
                t = (*finT2) + (-(*xi) * (*finT1));
                //Push onto vector new s & t
                sVec.push_back(s);
                tVec.push_back(t);

                ++xi;
                finT2 = tVec.begin()+(i+1);
                finT1 = tVec.begin()+(i+2);
                finS2 = sVec.begin()+(i+1);
                finS1 = sVec.begin()+(i+2);
                //cout << "S = " << s << " T = " << t << endl;
            }
            vector<InfInt> res;
            res.push_back(s);
            res.push_back(t);
            res.push_back(b);
            return res;
        }

        InfInt myModInverse(InfInt a, InfInt n)
        {
            InfInt gcd;//this is the gcd result
            InfInt inverse = -1;//By default -1, returns this value if no inverse if found in n attempts
            for(InfInt i = 0; i < n; i++)
            {
                gcd = myMod(a*i, n);
                if (gcd == 1){
                    inverse = i;
                    break;
                }
            }
            if (inverse == -1)
                return inverse;
            else
                return myMod(inverse, n);
        }

        InfInt myChinese(InfInt a, InfInt m, InfInt b, InfInt n)
        {
            //The beast
            //x congruent (a mod m) && x congruent b (mod n) version (Two Congruence)
            vector<InfInt> euVec = myGCDex(m, n);
            auto sP = euVec.begin();
            auto tP = euVec.begin() + 1;
            //auto gcdP = euVec.end();
            cout << "gcdP == "<< *sP << endl;
            if (myGCD(m, n) != 1)
                return -1;//Cannot preform if GCD is not one
            
            InfInt res = (b * m * (*sP)) + (a * n * (*tP));
            if (res < 0)
                res = (m*n) + res;
            return res;
        }

        InfInt myGenChinese(vector<InfInt> a, vector<InfInt> m)
        {
            int i = 0;
            InfInt x = 0;
            InfInt mk = *m.begin();
            //Validity check
            for(auto mCheck = m.begin(); mCheck < m.end()-1; mCheck++)
            {   
                if(myGCD((*mCheck), (*mCheck+1)) == -1)
                    return -1;
                mk *= *(mCheck+1);
            }
            //Function Loop
            auto mCount = m.begin();
            
            for(auto gg = a.begin(); gg < a.end(); gg++)
            {
                InfInt z = 1;//Initailze z[i]
                int i2 = 0;
                //z loop
                
                for(auto zCount = m.begin(); zCount < m.end(); zCount++)
                {
                    //cout << "i2 i " << i2 << " " << i << endl;
                    if (i2 != i)
                        z *= *zCount;
                    //cout << z << " ";
                    i2++;
                }
                //printf("\n");
                //y[i] is inverse of z[i]
                InfInt zy = myMod(z, (*mCount));
                InfInt y = myModInverse(zy, (*mCount));
                //cout << "y = " << y << " mCount = " << *mCount << endl;
                InfInt curA = myMod(*gg, (*mCount));//Deals with negatives
                //cout << "x += " << curA << " * " << z << " * " << y << endl;
                x += (curA) * (z) * (y);//gg is a[i]
                mCount++;
                i++;
            }
            return myMod(x, mk);
        }

        InfInt myPowMod(InfInt a, InfInt b, InfInt n)
        {
            InfInt pow2 = 1;//1 2 4 8 16 32 ...
            InfInt res = 1;
            //InfInt base = 2;
            InfInt remainder;
            int counter = 0;
            InfInt tempA;
            while(b != 0)
            {
                remainder = b % 2;
                b = b/2;
                if (counter == 0)
                    pow2 = myMod(a, n);
                else
                    pow2 = myMod((pow2 * pow2), n);
                
                if (remainder == 1)//AKA the bit is turned on
                    res = myMod((res * pow2), n);
                counter++;
                //cout << pow2 << " ";
            }
            //printf("\n");
            return res;
        }
};

#endif // CRYPTO_H_INCLUDED
