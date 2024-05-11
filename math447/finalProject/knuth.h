#ifndef KNUTH_H_INCLUDED
#define KNUTH_H_INCLUDED

#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#include <fstream>

using namespace std;

class KnuthFunc
{
    private:
        //Resets the position of the In File Stream to 0 and removes the EOF flag with clear
        void streamReset(ifstream& s)
        {
            s.clear();
            s.seekg(0);
        }

        //Tests
        //Determines the correlation coefficent, aka how much the previous number depends on the previous
        float serialCorrTest(ifstream& s)
        {
            int X0, Xj, Xji;
            int n = 1;//Our count
            long numer = 0;//n(X0*X1+X1*X2+.....+Xn-2*Xn-1+Xn-1+X0)
            long subtractor = 0;//(X0 + X1 + ... + Xn-1)^2
            long denom = 0;//n(X0^2 + X1^2 + ... + Xn-1^2)
            s >> X0;
            Xj = X0;
            while(s >> Xji){
                //Numerator One Calc
                numer += (Xj*Xji);
                //Subtractor Calc, used in both numerator && denomonator
                subtractor += Xj;
                //Denomonator One Calc
                denom += (Xj*Xj);
                n++;
                Xj = Xji;
            }
            //Final calcs
            numer += (X0*Xji);
            numer *= n;
            subtractor *= subtractor;
            denom *= n;
            long pt1 = (numer - subtractor);
            long pt2 = (denom - subtractor);
            float coeff = (float)pt1/(float)pt2;
            streamReset(s);
            return coeff;
        }
        //Not the knuth version but I am taking the average of the difference between xj and xj1
        float avgDifTest(ifstream& ciphertxt)
        {
            int Xj, Xj1;
            int gap = 0;
            int count = 0;
            ciphertxt >> Xj;
            while(ciphertxt >> Xj1){
                gap += abs(Xj1 - Xj);
                count++;
                Xj = Xj1;
            }
            float avg = (float)gap/(float)count;
            streamReset(ciphertxt);
            return avg;
        }
        bool gapTest(){
            return true;
        }
        //Knuth page 66
        bool runUpTest(ifstream& ciphertxt)
        {
            //Whenever Xj > Xj+1, seperate the sequence from the rest and get
            //The length of the run i.e. 1 2 3 4 2 8 7 would be
            // 1 2 3 4 | 2 8 | 7 and the length are 4, 2, and 1
            int runLength = 1;
            int numRuns = 0;
            int Xj, Xj1;
            int avgl = 0;
            int n;//Length of ciphertext aka sequence
            ciphertxt >> Xj;
            while(ciphertxt >> Xj1){
                if (Xj > Xj1){
                    numRuns++;
                    avgl += runLength;
                    runLength = 1;
                    ciphertxt >> Xj;
                }
                else{
                    runLength++;
                    Xj = Xj1;
                }
                n++;
            }
            printf("Number of Up Runs are %d\nAverage Run Length was %f\n", numRuns, ((float)avgl/(float)numRuns));
            streamReset(ciphertxt);
            return true;
        }

        bool runDownTest(ifstream& ciphertxt)
        {
            int runLength = 1;
            int numRuns = 0;
            int Xj, Xj1;
            int avgl = 0;
            int n;//Length of ciphertext aka sequence
            ciphertxt >> Xj;
            while(ciphertxt >> Xj1){
                if (Xj < Xj1){
                    numRuns++;
                    avgl += runLength;
                    runLength = 1;
                    ciphertxt >> Xj;
                }
                else{
                    runLength++;
                    Xj = Xj1;
                }
                n++;
            }
            printf("Number of Down Runs are %d\nAverage Run Length was %f\n", numRuns, ((float)avgl/(float)numRuns));
            streamReset(ciphertxt);
            return true;
        }

        //Solid chance that I am not going to do this one
        bool subSequenceTest()
        {
            return true;
        }

        //Dr. Hammer used something like this to find the distribution of integers when reduced by mod 26,
        //So not a bad idea to do the same on mine but get the average for that distribution.
        float modReducTest(ifstream& s, int m)
        {
            int x;
            int n = 0;
            float avg = 0;
            //s >> Xj;
            while(s >> x){
                avg += (x%m);
                //printf("%d ", (x%m));
                n++;
            }
            avg/=(float)n;
            streamReset(s);
            return avg;
        }

        void digitFrequencyTest(ifstream& s)
        {
            int digitArr[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            int x, a, g;
            float avg = 0;
            int n = 0;
            while(s >> x){
                a = x;
                for(int i = 0; i < ((int)log10(x)+1); i++){
                    g = a%10;
                    digitArr[g]++;
                    avg += g;
                    //a -= g;
                    if (a!=0)
                        a /= 10;
                    n++;
                }
            }
            //print array
            for(int i = 0; i < 9; i++)
                printf("Number of %ds are %d\n", i, digitArr[i]);
            printf("Average Digit is %f\n", (avg/(float)n));
            streamReset(s);
        }

    public:
        //Runs all the tests and prints the results of each
        bool testValidity(ifstream &s){
            bool uRun = runUpTest(s);
            bool dRun = runDownTest(s);
            float dgap = avgDifTest(s);
            printf("Average Gap between numbers is %f\n", dgap);
            float corrCoef = serialCorrTest(s);
            printf("Correlation Coefficient is %f\n", corrCoef);
            float modRed = modReducTest(s, 26);
            printf("Average Mod Reduction value is %f\n", modRed);
            digitFrequencyTest(s);
            return true;
        }
};

#endif //KNUTH_H_INCLUDED