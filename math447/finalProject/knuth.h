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
        string ciphertext;
        //Tests
        //This one is ging to be very painful to program :(
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
            int oneRun = 0;
            int twoRun = 0;
            int threeRun = 0; 
            int fourRun = 0; 
            int bigRun = 0;
            int avgl = 0;
            int n;//Length of ciphertext aka sequence
            ciphertxt >> Xj;
            while(ciphertxt >> Xj1){
                if (Xj > Xj1){
                    //Will edit this ugly if statement tower
                    if(runLength == 1)
                        oneRun++;
                    else if(runLength == 2)
                        twoRun++;
                    else if(runLength == 3)
                        threeRun++;
                    else if(runLength == 4)
                        fourRun++;
                    else
                        bigRun++;
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
            //printf("One Length Runs: %d\nTwo Length Runs: %d\nThree Length Runs: %d\nFour Length Runs: %d\nFive and Above Length Runs: %d\n", oneRun, twoRun, threeRun, fourRun, bigRun);
            return true;
        }

        bool runDownTest(ifstream& ciphertxt)
        {
            int runLength = 1;
            int numRuns = 0;
            int Xj, Xj1;
            int oneRun = 0;
            int twoRun = 0;
            int threeRun = 0; 
            int fourRun = 0; 
            int bigRun = 0;
            int avgl = 0;
            int n;//Length of ciphertext aka sequence
            ciphertxt >> Xj;
            while(ciphertxt >> Xj1){
                if (Xj < Xj1){
                    //Will edit this ugly if statement tower
                    //printf("In down");
                    if(runLength == 1)
                        oneRun++;
                    else if(runLength == 2)
                        twoRun++;
                    else if(runLength == 3)
                        threeRun++;
                    else if(runLength == 4)
                        fourRun++;
                    else
                        bigRun++;
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
            //printf("One Length Runs: %d\nTwo Length Runs: %d\nThree Length Runs: %d\nFour Length Runs: %d\nFive and Above Length Runs: %d\n", oneRun, twoRun, threeRun, fourRun, bigRun);
            return true;
        }

        bool subSequenceTest()
        {
            return true;
        }

    public:
        //Setter for the value of the ciphertext
        void setCiphertext(string ct)
        {
            ciphertext = ct;
        }

        //Runs all the tests and prints the results of each
        bool testValidity(ifstream &s){
            bool uRun = runUpTest(s);
            s.clear();
            s.seekg(0);
            bool dRun = runDownTest(s);
            s.clear();
            s.seekg(0);
            float dgap = avgDifTest(s);
            printf("Average Gap between numbers is %f\n", dgap);
            s.clear();
            s.seekg(0);
            float corrCoef = serialCorrTest(s);
            printf("Correlation Coefficient is %f\n", corrCoef);
            //if (uRun, dRun)
            //    return true;
            //else
            //    return false;
            return true;
        }
};

#endif //KNUTH_H_INCLUDED