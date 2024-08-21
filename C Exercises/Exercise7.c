#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

bool isMIncreasing(int* someArray, int size){
    
    int i;
    bool isMInc = true;
    for (i = 1; i < size; i++){
        if (someArray[i-1] > someArray[i]){
            isMInc = false;
        }
    }

    return isMInc;
}

bool isMDecreasing(int* someArray, int size){

    int i;
    bool isMDec = true;
    for (i = 1; i < size; i++){
        if (someArray[i-1] < someArray[i]){
            isMDec = false;
        }
    }

    return isMDec;

}

bool isMonotonic(int* someArray, int size){

    if (size == 1){
        return true;
    }


    return (isMDecreasing(someArray, size) || isMIncreasing(someArray, size));
}

int main() {

    return 0;
}