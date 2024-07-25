#include <stdio.h>
#include "main.h"
#define SIZE 2

int main(){

    int loop;
    int testArray[4] = {2, 4, 5, 6};
    int* testPointer = testArray;
    int target = 7;
    int* arrayToPrint = twoSum(testPointer, target);

    printf("[");

    for (loop = 0; loop < SIZE; loop++){
        
        if (loop == SIZE - 1){
            printf("%d", arrayToPrint[loop]);
        }
        
        else {
            printf("%d, ", arrayToPrint[loop]);;
        }
    }

    printf("]\n");



    return 0;
}

int* twoSum(int* nums, int target){
    int i;
    int j;
    static int returnArray[2] = {-1, -1};
    int arraysize = sizeof(nums) / 2;

    for (i = 0; i < arraysize; i++){
        for (j = i + 1; j < arraysize; j++){
            int sum = nums[i] + nums[j];
            if (sum == target){
                returnArray[0] = i;
                returnArray[1] = j;
            }
        }
    }

    printf("%d %d\n", returnArray[0], returnArray[1]);

    int* retPointer = returnArray;

    printf("%d %d\n", retPointer[0], retPointer[1]);
    printf("%d\n", &retPointer[1]);

    return retPointer;
}

