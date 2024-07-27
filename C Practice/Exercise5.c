#include <stdio.h>
#include <stdlib.h>
#include "main5.h"

int main() {

    static int test[6] = {7,1,5,3,6,4};
    int length = sizeof(test) / sizeof(test[0]);
    printf("The best time to sell is %d and the best time to buy is %d!\n", getMax(test, length), getMin(test, length));
    return 0;
}

int getMin(int* array, int length){
   
   int i = 0;
   int min = 10000000;

   for (i = 0; i < length; i++) {
        if (min > array[i]){
            min = array[i];
        }
   } 

   return min;
}

int getMax(int* array, int length){
   
   int i = 0;
   int max = -10000000;

   for (i = 0; i < length; i++) {
        if (max < array[i]){
            max = array[i];
        }
   } 

   return max;
}
