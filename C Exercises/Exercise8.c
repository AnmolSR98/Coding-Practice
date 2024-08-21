#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    // the solution should work more on a log(n+m) complexity, as opposed to the blunt way of doing thing
    // should be a binary search on the first array, combined with a binary search on the second array

    if ( (nums1Size == 0) && (nums2Size == 0) ) {
        return 0.0;
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

double generateGuesses(int* nums1, int nums1Size, int* nums2, int nums2Size) {

}

double generateMedian(int* nums, int numsSize){

    if (numsSize % 2 == 0) {
        return ( nums[ (numsSize / 2) - 1 ] + nums[ numsSize / 2 ] ) / 2; 
    }

    return nums[ numsSize / 2 ];
}

int main(){
    return 0;
}