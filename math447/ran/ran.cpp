#include <iostream>
#include <random>

using namespace std;

int main(){
    //Generate a random string of non repeating numbers for a fake computer generated "cipheretxt"
    srand(time(0));
    int arr[943];
    for(int i = 0; i < 702; i++){
        int index = 1+rand()%943;
        if (arr[index] == 1)
            continue;
        else{
            printf("%d ", index);
            arr[index] = 1;
        }
    }
}