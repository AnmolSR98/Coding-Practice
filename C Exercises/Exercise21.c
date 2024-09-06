#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

// quickly writing an absolute value function
int getAbs(int a, int b) {

    if (a <= b) {
        return (b - a);
    }

    return (a - b);
}

// code to get the maximum gap between the two elements in an array, after it has been sorted
int maximumGap(int* nums, int numsSize) {

    if ((numsSize == 0) || (numsSize == 1)) {
        return 0;
    }

    // might be faster to use binary search tree, with modded method
    // or start from either end


    return 0;
}


int main() {
    
    return 0;
}