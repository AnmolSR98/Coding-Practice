// coding an algorithm to find a container with the most water
// going to just do this via a simple brute force solution to spare my mind of burdensome thoughts
#include <stdlib.h>
#include <stdio.h>

// simple function to quickly get the minimum of two numbers
int getMin(int a, int b){
    if (a < b){
        return a;
    }

    return b;
}

// actual function here
int getMostWater(int* someArray, int length){

    // basic guard
    if (length < 2){
        return -1;
    }

    // set as a negative integer to be rewritten
    int maxWater = -1;
    int i;

    // i is the lengths that will be tested, from 1 all the way to the length -1
    for (i = length - 1; i > 0; i--){
        int j;
        // check each pair that exists with space of i 
        for (j = 0; i + j < length; j++){

            // get the height of the water
            int immHeight = getMin(someArray[j], someArray[i+j]);
            // check whether it needs to be updated if this is the larger water
            if (i*immHeight > maxWater){
                maxWater = i*immHeight;
            }
        }
    }

    return maxWater;
}


int main(){
    int test[10] = {9, 34, 83, 36, 43, 95, 20, 28, 63, 12};
    int length = 10;
    printf("%d\n", getMostWater(test, length));

    int test2[9] = {1,8,6,2,5,4,8,3,7};
    length = 9;
    printf("%d\n", getMostWater(test2, length));

    return 0;
}