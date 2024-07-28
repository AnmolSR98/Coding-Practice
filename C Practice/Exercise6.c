#include <stdio.h>
#include "main6.h"

int main() {

    int test_1[5] = {1, 2, 3, 4, 2};
    int test_2[5] = {1, 2, 3, 4, 5};
    printf("0 for false, 1 for true: %d\n", containsDuplicates(test_1, 5));
    printf("0 for false, 1 for true: %d\n", containsDuplicates(test_2, 5));
    return 0;
}

// 0 FOR FALSE, 1 FOR TRUE
int containsDuplicates(int* array, int length) {

    int i, j = 0;
    int hasDup = 0, currentIndex = 0;
    int dupes[length];

    for (i = 0; i < length; i++) {

        for (j = 0; j < currentIndex; j++){
            if (array[i] == dupes[j]){
                return 1;
            }
        }

        dupes[currentIndex] = array[i];
        currentIndex++;

    }

    return 0;
}