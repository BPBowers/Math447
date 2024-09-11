#include <iostream>
#include <fstream>
#include <map>
#include <random>
#include "func.h"

using namespace std;

int main(){
    CTGen gen;
    //ifstream keyDoc("../finalProject/CipherTexts/declaration.txt");
    ifstream keyDoc("../finalProject/CipherTexts/declaration.txt");
    ifstream message("msg.txt");//Message to be encrypted
    ofstream outDoc("ciphertext3.txt");

    string readBuff;
    char firstLetter, charBuff;
    int count;
    while(keyDoc>>readBuff)
        count++;

    keyDoc.clear();
    keyDoc.seekg(0);

    char keyPair[count];
    //printf("Mad it past\n");
    //Generate the keyPairs for the key document
    for(int i = 0; keyDoc >> readBuff; i++)
    {
        firstLetter = *readBuff.begin();
        keyPair[i] = tolower(firstLetter);
    }

    //Encrypt Message
    srand(time(0));
    for(int i = 0; message >> charBuff; i++){
        charBuff = tolower(charBuff);
        int index = 1+rand()%(count%2000);
        bool pass = false;
        while(true)
        {
            if(keyPair[index] == charBuff){
                keyPair[index] = '@';
                break;
            }
            else if (index >= count && !pass){
                index = 0;
                pass = true;
            }
            else if (index >= count && pass)
            {
                printf("Failed to find the needed character, aborting %c %d\n", charBuff, index);
                return 0;
            }
            index++;
        }
        outDoc << index;
        outDoc << " ";
    }
}