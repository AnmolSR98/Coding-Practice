// file for the 3 sum problem on leetcode
// will test later, just too tired for now []
#include <stdio.h>
#include <stdlib.h>



int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    
    int** returnArray = malloc(sizeof(int)* numsSize);
    int currentIndex = 0;
    int i, j, k;
    
    for (i = 0; i < numsSize; i++) {
        for (j = 1; j < numsSize; j++) {
            for (k = 2; k < numsSize; k++) {
                if ((nums[i] + nums[j] + nums[k] == 0) && (i != j) && (j != k) && (i != k)) {

                    int holder[3] = {i, j, k};
                    returnArray[currentIndex] = holder;
                    currentIndex += 1;
                }
            }
        }
    }

    return returnArray;
}

int main() {

    int nums[6] = {-1,0,1,2,-1,-4};



    return 0;
}