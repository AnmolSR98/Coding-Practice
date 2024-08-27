// file for the 3 sum problem on leetcode
// will test later, just too tired for now 
// need to remove the stuff that results in duplicates []
// also figure out how to do nested arrays []
#include <stdio.h>
#include <stdlib.h>

void printArray(int* someArray, int length){
    printf("[ ");
    int i ;
    for (i = 0; i < length - 1; i++){
        printf("%d, ", someArray[i]);
    }
    printf("%d ]", someArray[length - 1]);

}

// use this for factorial
int factorial(int n){
    return 0;
}


// use this when allocating
int nCr(int n, int r){
    return 0;
}

// use this for the dupes
int* getRidOfDupes(){
    return 0;
}

// use this to sort the array
void insertionSort(){

}


int** threeSum(int* nums, int numsSize) {
    
    int totalLength;
    int i, j, k, immlength = 3; 
    for (i = 0; i < numsSize; i++) {
        for (j = i+1; j < numsSize; j++) {
            for (k = j+1; k < numsSize; k++) {
                if ((nums[i] + nums[j] + nums[k] == 0) && (i != j) && (j != k) && (i != k)) {
                   totalLength += 1;
                }
            }
        }
    }

    int currentIndex = 0;
    int** returnArray = malloc(sizeof(int)* totalLength);

    for (i = 0; i < numsSize; i++) {
        for (j = i+1; j < numsSize; j++) {
            for (k = j+1; k < numsSize; k++) {
                if ((nums[i] + nums[j] + nums[k] == 0) && (i != j) && (j != k) && (i != k)) {
                    int *holder = malloc( sizeof(int) * immlength );
                    holder[0] = i, holder[1] = j, holder[2] = k;
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
    int* returnSize[6];
    int length = 6;

    int** test = malloc(sizeof(int)*3);
    test = threeSum(nums, length);
    
    int i, j;
    printf("[ ");
    for (i = 0; i < 3; i++) {
        printArray(test[i], 3);
        printf(", ");
    }
    printf(" ]\n");

    return 0;
}