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

        //Autocorrelation Test
        //Computation of autocorrelation between every m numbers (m known as lag) starting with ith number
        //Autocorrelation R[i], R[i+m], R[i+2m], 
        //M is largest Integer s.t. i+(M+1)m <= N (max number)
        //Non zero autocor implies lack of dependence so following detailed test
        //Weird part: zetaNot = Row/Sigma;
        //zetaNot is a uniform distribution table
        //Row[im] = (1/M+1)*(Sum R[i+Km]*R[i+(K+1)m])-0.25
        //Sigma = sqrt(13M+7/12(M+1))
        //if zeta less than accept, more reject
        void autoCorTest(ifstream&s)
        {
            //
            streamReset(s);
        }


        //Komlmogorov-Smirnov Test
        bool ksTest(ifstream& s, int n)
        {
            float d, dCan, dAlpha;
            int temp;
            int arr[n];
            //1.)Sort list in assending order
            for(int i = 0; s >> temp; i++)
                arr[i] = temp;
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n - i - 1; j++){
                    if(arr[j] > arr[j + 1]){
                        temp = arr[j];
                        arr[j] = arr[j + 1];
                        arr[j + 1] = temp;
                    }
                }
            }

            //2.) Compute d+ = max{(1/n)-arr[i]}
            float dPlus = 0;
            for(int i = 0; i < n; i++){
                dCan = ((i+1)/n)-arr[i];
                if (dCan > dPlus)
                    dPlus = dCan;//dPlus become the cannidate
            }
            //3.) Compute d- = max{arr[i]-(i-1)/n}
            float dMinus = 0;
            for(int i = 0; i < n; i++){
                dCan = arr[i] - ((i-1)/n);
                if (dCan > dMinus)
                    dPlus = dCan;//dPlus become the cannidate
            }
            //4.) d is the maximum between dMinus and dPlus
            d = max(dPlus, dMinus);
            //5.) Alpha is hard coded at 0.05, dAlpha is gained from the KST characteristic table, buut 
            dAlpha = (1.35810/(float)sqrt(n));
            streamReset(s);
            if (d < dAlpha)
                return true;//True meaning random
            else
                return false;//False meaning not random
        }

        //Values of arr will be compared against expected outcome
        //k is the number of possible buckets each result can become
        //dataPool is the total entries that were used to create a decent prediction value
        //mode determines if the chi Square will be used with English Language Frequencies or posses an equal distribution of 1/k
        bool chiSquare(int* arr, int k, float dataPool, int mode)
        {
            //Only using values from the 0.05 percentage column, and only up to degree of freedom 30
            float chiTable[] = {3.841, 5.991, 7.815, 9.488, 11.070, 12.592, 14.067, 15.507, 16.919, 18.307,
                              19.675, 21.026, 22.362, 23.685, 24.996, 26.296, 27.587, 28.869, 30.144, 31.410,
                               32.671, 33.924, 35.172, 36.415, 37.652, 38.885, 40.113, 41.337, 42.557, 43.773};
            //I guess we assuming n = 26
            float letterFrequency[] = {8.4966, 2.0720, 4.5388, 3.3844, 11.1607, 1.8121, 2.4705, 3.0034, 7.5448,
                                       0.1965, 1.1016, 5.4893, 3.0129, 6.6544, 7.1635, 3.1671, 0.1962, 7.5809,
                                       5.7351, 6.9509, 3.6308, 1.0074, 1.2899, 0.2902, 1.7779, 0.2722};
            float p[k];
            for (int i = 0; i < k; i++){
                p[i] = 0;
            }
            //(i+x)%26
            float temp;
            for (int x = 0; x < ((k-1)*mode)+1; x++){
                for(int i = 0; i < k; i++){
                    if (mode == 1)
                        temp = letterFrequency[((i+x)%k)]/100;
                    else
                        temp = (1/(float)k);
                    p[i] = dataPool*temp;
                    //printf("np %f\n", p[i]);
                }
                float value = 0;
                
                //value = ((O-np)^2)/np + all other posibilities
                for(int i = 0; i < k; i++){
                    value += ((float)(arr[i] - p[i]))*(arr[i] - p[i])/(p[i]);
                    //value += ((float)pow(arr[i], 2)/(letterFrequency[i]/100))-(float)dataPool;
                    //printf("This is value %f\n", value);
                    //printf("This is arr %d\n", arr[i]);

                }
                //value *= (1/(float)dataPool);
                //printf("This is value %f\n This is chiTable %f\n", value, chiTable[n-2]);
                if(value <= chiTable[k-2])//Degree of freedom is n-1, but -2 b.c. arrays start at index 0 duh
                    return true;
                else
                    continue;
            }
            return false;
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
        //Only using the beginning part of the algorithm to get the number of runs, 
        //might also modify to return an array of the run amounts for up && down
        int runUpTest(ifstream& ciphertxt, ofstream& out)
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
                //Xj = Xj1;
                n++;
            }
            //printf("Number of Up Runs are %d\nAverage Run Length was %f\n", numRuns, ((float)avgl/(float)numRuns));
            out << "Number of Up Runs are "<< numRuns << "\nAverage Run Length was " << ((float)avgl/(float)numRuns) << "\n";
            streamReset(ciphertxt);
            return n;
        }
        //Same desc as above
        bool runDownTest(ifstream& ciphertxt, ofstream& out)
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
                //Xj = Xj1;
                n++;
            }
            //printf("Number of Down Runs are %d\nAverage Run Length was %f\n", numRuns, ((float)avgl/(float)numRuns));
            out << "Number of Down Runs are "<< numRuns << "\nAverage Run Length was " << ((float)avgl/(float)numRuns) << "\n";
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
        //Need to modify
        float modReducTest(ifstream& s, int m, ofstream& out)
        {
            int x;
            int n = 0;
            float avg = 0;
            int arr[m];
            for (int i = 0; i < m; i++)
                arr[i] = 0;
            //s >> Xj;
            while(s >> x){
                int temp = (x%m);
                arr[temp]++;
                avg += (temp);
                //printf("%d ", (x%m));
                n++;
            }
            avg/=(float)n;
            streamReset(s);

            //for(int i = 0; i < m; i++)
            //    printf(" %d ", arr[i]);
            //Now chiSquare time

            bool result = chiSquare(arr, m, n, 0);
            bool result2 = chiSquare(arr, m, n, 1);
            //printf("Chi-Square even distribution: %d\nChi-Square English Language distribution: %d\n", result, result2);
            out << "Chi-Square even distribution: "<< result << "\nChi-Square English Language distribution: " << result2 << "\n";
            return avg;
        }
        //Right keeps track of how many times each digit appears on a ciphertext and also prints average digit.
        void digitFrequencyTest(ifstream& s, ofstream& out)
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
                    if (a!=0)
                        a /= 10;
                    n++;
                }
            }
            out << "Last digit chi-square result: " << chiSquare(digitArr, 9, n, 0) << "\n";
            
            //print array loop
            for(int i = 0; i < 9; i++)
                out << "All digits number of " << i <<"s are " << digitArr[i] << "\n";
            //printf("Number of %ds are %d\n", i, digitArr[i]);
            //printf("Average Digit is %f\n", (avg/(float)n));
            out << "All digits average Digit is " << (avg/(float)n) << "\n";
            streamReset(s);
        }

        void lastDigitFreq(ifstream& s, ofstream& out)
        {
            int digitArr[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            int x, a;
            float avg = 0;
            int n = 0;
            while(s >> x){
                a = x%10;
                digitArr[a]++;
                avg += a;
                n++;
            }
            
            out << "Last digit chi-square result: " << chiSquare(digitArr, 9, n, 0) << "\n";
            for(int i = 0; i < 9; i++)
                out << "Last digit number of " << i <<"s are " << digitArr[i] << "\n";
            out << "Last digit average digit is " << (avg/(float)n) << "\n";
            streamReset(s);
        }

    public:
        //Runs all the tests and prints the results of each
        bool testValidity(ifstream &s, ofstream& out){
            //bool uRun = runUpTest(s);
            int n = runUpTest(s, out);
            bool dRun = runDownTest(s, out);
            float dgap = avgDifTest(s);
            //printf("Average Gap between numbers is %f\n", dgap);
            out << "Average Gap between numbers is " << dgap << "\n";
            float corrCoef = serialCorrTest(s);
            //printf("Correlation Coefficient is %f\n", corrCoef);
            out << "Correlation Coefficient is " << corrCoef << "\n";
            float modRed = modReducTest(s, 26, out);
            //printf("Average Mod Reduction value is %f\n", modRed);
            out << "Average Mod Reduction value is " << modRed << "\n";
            digitFrequencyTest(s, out);
            lastDigitFreq(s, out);
            bool ksRes = ksTest(s, n);
            //printf("ksTest pass = %d\n", ksRes);
            out << "ksTest pass = " << ksRes << "\n";
            printf("Tests Complete!\n");
            return true;
        }
};

#endif //KNUTH_H_INCLUDED