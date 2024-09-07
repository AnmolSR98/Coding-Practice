#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

int maxProductSubarray(int* nums, int numsSize) {

    if ((numsSize == 0) || (numsSize == 1)) {
        return 0;
    }

    int currentMaxProduct = -2000000000;
    int i;

    for (i = 0; i < numsSize - 1; i++) {
        
        if ((nums[i] * nums[i + 1]) > currentMaxProduct) {
            currentMaxProduct = nums[i] * nums[i + 1];
        }
    }

    return currentMaxProduct;
}

int main() {

    int test1[10] = {12, 18, 3, 10, 5, 7, 11, 2, 6, 20}; // 6
    int test2[10] = {11, 16, 19, 1, 15, 9, 4, 5, 14, 20}; // 4
    int test3[10] = {10, 2, 6, 3, 14, 5, 12, 16, 15, 11}; // 4

    int gap1 = maxProductSubarray(test1, 10);

    return 0;
}