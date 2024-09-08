#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// TRY TO FIX THIS LATER, TRY RADIX SORT
// simple swap function
void swap(int a, int b, int* nums) {

}

int getDigitAtPosition(int position, int number) {

    int valuesHigher = (number / (int) pow(10, position)) * (int) pow(10, position);

    number = number - valuesHigher;
    
    number = number / ((int) pow(10, (int) log10(number))); 

    return number;
}

int getMax(int* nums, int numsSize) {
    int i, max = -2000000000;
    for (i = 0; i < numsSize; i++) {
        if (max < nums[i]) {
            max = nums[i];
        }
    }

    return max;
}

/**
// implementing radix sort
void radixSort(int* nums, int numsSize) {

    int max = getMax(nums, numsSize);
    int intLength = (int) log10(max);
    int i, j;

    for (i = 1; i < intLength; i++) {
        for (j = 0; j < numsSize; j++) {

        }
    }


}
**/

int main() {
    
    int test1[10] = {12, 18, 3, 10, 5, 7, 11, 2, 6, 20}; // 6
    int test2[10] = {11, 16, 19, 1, 15, 9, 4, 5, 14, 20}; // 4
    int test3[10] = {10, 2, 6, 3, 14, 5, 12, 16, 15, 11}; // 4

    int gap1 = getDigitAtPosition(4, 1723);

    printf("Digit is: %d\n", gap1);

    return 0;
}