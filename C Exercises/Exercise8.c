#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int generateMedian(int* nums, int numsSize){

    if (numsSize % 2 == 0) {
        return ( nums[ (numsSize / 2) - 1 ] + nums[ numsSize / 2 ] ) / 2; 
    }

    return nums[ numsSize / 2 ];
}

int findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {

    // the solution should work more on a log(n+m) complexity, as opposed to the blunt way of doing thing
    // should be a binary search on the first array, combined with a binary search on the second array
    // the solution prolly doesn't involve merging the two arrays first

    if ( (nums1Size == 0) && (nums2Size == 0) ) {
        return 0;
    }

    else if (nums1Size == 0) {
        return generateMedian(nums2, nums2Size);
    }

    else if (nums2Size == 0) {
        return generateMedian(nums1, nums1Size); 
    }
    
    else {
        
    }

}

// suboptimal solution 
int generateGuesses(int* nums1, int nums1Size, int* nums2, int nums2Size) {

}

// binary search that finds the index of the next smallest if the actual value can't be found
int moddedBinSearch(int* someArray, int length, int low, int high, int target) {

    // termination condition where the low index is higher than the high index
    if (low > high) {

        // the low value is greater than the target, then the high must be the next smallest element
        if (someArray[low] > target) {
            return high;
        }       

        // the low is smaller than the target, then it is the next smallest element
        else {
            return low;
        }
    }

    // termination condition where the two are equal
    else if (low == high){

        // if the is greater than the target, the index prior is the next smallest element
        if (someArray[high] > target){
            return high - 1;
        }

        // otherwise, the high is next smallest element
        else {
            return high;
        }
    }

    else {

        int guessIndex = ( low + high ) / 2;
        int guess = someArray[guessIndex];

        // if the guess is correct, return the index
        if (guess == target)  {
            return guessIndex;
        }

        // if it is smaller, then check the lower half
        else if (guess < target) {
            return moddedBinSearch(someArray, length, guessIndex+1, high, target);
            
        }

        // if it is larger than the target scan, the lower half of it 
        else {
            return moddedBinSearch(someArray, length, low, guessIndex-1, target);
        }
    }


}


int main(){
    
    int test1[10] = {2, 9, 14, 18, 26, 42, 46, 76, 83, 98};
    int test2[10] = {18, 21, 24, 44, 67, 74, 77, 79, 83, 96};
    int length = 10;
    int low = 0;
    int high = length - 1;
    int target = 1;
    int i;
    
    for (i = 0; i < length; i++) {
        int closest = moddedBinSearch(test1, length, low, high, target);
        printf("%d %d: %d\n", target, test1[closest], closest);
        target += 12;
    }
    
    return 0;
}