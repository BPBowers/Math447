#ifndef KNUTH_H_INCLUDED
#define KNUTH_H_INCLUDED

#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>

using namespace std;

class KnuthFunc
{
    private:
        string ciphertext;
        //Tests
        //This one is ging to be very painful to program :(
        bool serialCorrTest()
        {
            return true;
        }
        //
        bool gapTest()
        {
            return true;
        }
        //Knuth page 66
        bool runUpTest()
        {
            //Whenever Xj > Xj+1, seperate the sequence from the rest and get
            //The length of the run i.e. 1 2 3 4 2 8 7 would be
            // 1 2 3 4 | 2 8 | 7 and the length are 4, 2, and 1
            return true;
        }

        bool runDownTest()
        {
            //Whenever Xj < Xj+1,
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
        void testValidity(string ct){
            setCiphertext(ct);
            //Run Serial Correlation Test
            serialCorrTest();
            gapTest();
            runUpTest();
            runDownTest();
            subSequenceTest();
        }
};

#endif //KNUTH_H_INCLUDED