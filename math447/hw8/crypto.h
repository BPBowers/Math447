#ifndef CRYPTO_H_INCLUDED
#define CRYPTO_H_INCLUDED

#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
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
            //printf("made it into pow mod\n");
            InfInt remainder;
            int counter = 0;
            InfInt tempA;
            while(b != 0)
            {
                remainder = b % 2;
                b = b/2;
                if (counter == 0){
                    //pow2 = myMod(a, n);
                    pow2 = a%n;
                }
                else{
                    //pow2 = myMod((pow2 * pow2), n);
                    pow2 = (pow2*pow2)%n;
                }
                if (remainder == 1){//AKA the bit is turned on
                    //res = myMod((res * pow2), n);
                    res = (res*pow2)%n;
                }
                counter++;
                //cout << pow2 << " ";
            }
            //printf("\n");
            return res;
        }
//********************************
//Homework 6 additions
//********************************
        bool femat(InfInt n)
        {
            //1.) Create loop to generate 10 randomly chosen numbers
            //In the range of 2 <= k <= n-1
            //2.) Raise n-1 to each k (mod n), if any
            //are not equal to one, return false
            srand(time(0));
            //vector <InfInt> k;
            for (int i = 0; i < 10; i++)
            {
                InfInt k = (InfInt)2+((InfInt)rand()%(n-2));
                //cout << k << " goes to " << myPowMod(k, n-1, n) << endl;
                if (myPowMod(k, n-1, n) != 1)
                    return false;
            }
            return true;
        }

        InfInt eulerPhi(InfInt n)
        {
            //Brute force this one so you don't factor
            InfInt num;//Counter for result of the function
            for(InfInt i = 1; i <= n; i++)
            {
                if(myGCD(i, n) != 1)
                    continue;
                num++;
            }
            return num; //Returns number of numbers that are relatively prime
                        //to n in the interval [1, n].
        }

        bool primRoot(InfInt a, InfInt p)
        {
            //Tests if "a" is a primitive root (mod p).
            //Assume p is prime
            //Brute force all options (look in notes)
            //Check if has all numbers up to p;
            vector <InfInt> resVec;
            for (InfInt i = 1; i < p; i++)
            {
                //resVec.push_back(myPowMod(a, i, p));
                InfInt temp = myPowMod(a, i, p);
                resVec.push_back(temp);
                if(temp == 1)
                    break;
            }
            if ((InfInt)resVec.size() != (p-1))
                return false;
            //Sort Vector.
            std::sort(resVec.begin(), resVec.end());
            auto resIt = resVec.begin();
            for (InfInt i = 1; i < p; i++)
            {
                if(*resIt != i)
                    return false;
                resIt++;
            }
            return 1;
        }

        vector<InfInt> sqaureRootMod(InfInt a, InfInt p)
        {
            //Returns the sqaure roots (that is roots, vector??)
            //sq(a) (mod p) *check if each is congruent to 3 (mod 4)*
            //If not, return *vector* of -1s

           
            vector <InfInt> returnVec;
            //Check p is 3 mod 4
            //cout << p << endl;
            if(myMod(p, 4) != 3)
            {
                returnVec.push_back(-1);
                cout << "Huh!";
                return returnVec;
            }

            InfInt x1 = myPowMod(a, ((p-1)/4), p);
            InfInt nA, nX1, nX2;
            //vector <InfInt> returnVec;
            //Checks to see if it is a valid square root
            //If not, inverse of a mod p is instead valid
            if (myPowMod(x1, 2, p) != a)
            {
                nA = myModInverse(a, p);
                nX1 = myPowMod(nA, ((p-1)/4), p);
                nX2 = (myMod(-nX1, p));
                returnVec.push_back(nX1);
                returnVec.push_back(nX2);
                return returnVec;
            }
            //If valid, returns +- x
            InfInt x2 = myMod(-x1, p);
            returnVec.push_back(x1);
            returnVec.push_back(x2);
            return returnVec;
        }

        InfInt legendreSym(InfInt a, InfInt p)
        {
            //Returns Legendre symbol a/p
            //a/p == a^(p-1)/2 mod p

            //Assumes p is prime
            return myPowMod(a, ((p-1)/2), p);
        }

        InfInt jacobiSym(InfInt a, InfInt n)
        {
            //Assume n is odd
            //returns jacobi symbol of a/n

            //Must comfirm that GCD(a, n) =1, also comfirms n is odd
            if(myGCD(a, n) != 1 && n % 2 != 1)
                return -1;
            InfInt negCheck = 1;
            //InfInt twoCheck = 1;
            //cout<< a << " " << n << endl;
            while(true)
            {
                InfInt twoCheck = 1;
                //Rule 5: Check if m, n are congruent to 3 mod 4
                //If yes, swap and make negative, no just swap.
                if(myMod(a, 4) == 3 && myMod(n, 4) == 3)
                    negCheck *= -1;
                InfInt swap = a;
                a = n;
                n = swap;
                //Rule 2: Check if a % 2 = 0, if so, ((a/2)/n * 2/n)
                //Check if n is = 3, or 5 (mod 8) and determine
                //Result accorsdingly
                if(a%2 == 0)
                {
                    a /= 2;
                    if(myMod(n, 8) == 3 || 5)
                        twoCheck = -1;
                }

                negCheck *= twoCheck;
                if (a == 1 || a == -1)
                    break;
                //Rule 1: a = (b (mod n))
                a = myMod(a, n);
                //cout<< a << " " << n << endl;
            }
            //Rule 3: -1/n = -1^((n-1)/2)
            if (a == -1)
            {
                
                for (InfInt i = 0; i < ((n-1)/2); i++)
                    a *= a;
                negCheck *= a;
            }
            //cout<< a << " " << n << endl;
            return negCheck;
        }

        vector<InfInt> ratContFrac(InfInt a, InfInt b)
        {
            //Continued fraction for rational numbers a/b
            //Not sure how I'm going to do this one without decimals
            //So I take them in as InfInts, but this will still get the
            //Issue of the integers breaking down if they are too large
            //But cannot think of a different way of getting at the decimals
            //Other than maybe hunting down an Infinite double library
            vector<InfInt> returnVec;
            int intA = a.toInt();
            int intB = b.toInt();
            double residue = (double)intA/(double)intB;
            InfInt aI = 1;
            while(aI > 0)//Might change i < 10 to something else
            {
                aI = (int) residue;
                returnVec.push_back(aI);
                residue = 1/(residue - (aI.toInt()));
            }
            return returnVec;
        }

        vector<double> contFrac(double n, int length)
        {
            //"n" is a double, length determines how far you wish to
            //take the continued fraction
            vector<double> returnVec;
            
            //returnVec.push_back(n - ((int)n));
            for(int i = 0; i < length; i++){
                int antiRemain = (int) (n);
                returnVec.push_back(antiRemain);//Pushes a_i into return vector
                //cout << "This is anti " << antiRemain << endl;
                n = 1/(n - antiRemain);//Not attempting to solve the continued fraction, only looking for a_i values
            }
            return returnVec;
        }
        //Miller Rabin for HW8
        //n is the integer being tested
        //k is the maximum number of steps to be preformed
        void milRab(InfInt n, int t)
        {
            //Step One
            //n-1 = (2^t)*m
            InfInt m = (((n*n)-1)/2);
            //Step two
            //Take random "a" value 1 < a < n-1
            srand(time(0));
            InfInt a = (InfInt)2+((InfInt)rand()%(n-2));
            cout <<"This is the value of a for debug: " << a << endl;
            //Step Three
            //Compute b0 = a^m (mod n)
            // IF b0 = +-1 (mod n), n is possibly prime BREAK
            // OTHERWISE, continue to Step 4
            InfInt b = myPowMod(a, m, n);
            if(b == 1 || b == -1)
                cout<< n << " is probably prime!" << endl;
            else{
                //Step Four
                //Let b1 = b0^2 (mod n)
                // IF b1 = 1 (mod n), n is composite {can test by taking GCD(b0-1, n) = factor of n}
                // IF b1 = -1 (mod n), then n is possibly prime
                //Otherwise, Repeat 4 until hit bt-1, if not -1, then n is composite
                for(int i = 1; i < t; i++){
                    b = myPowMod(b, 2, n);
                    if(b == -1){
                        cout<< n << " is probably prime!" << endl;
                        break;
                    }
                    else if(b == 1 || i == t-1){
                        cout<< n << " is composite :(" << endl;
                        break;
                    }
                }
            }
            

        }
};

#endif // CRYPTO_H_INCLUDED
