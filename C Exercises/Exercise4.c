#include <stdio.h>
#include "main4.h"
#define maxsize 50

int main() {

    static char test1[8] = "hobos";
    static char test2[8] = "apple";
    // we know that this is working correctly ie. getUniques is working correctly
    printf("%d, %d\n", getUniques(test1), getUniques(test2));
    int test = isIsomorphic(test1, test2);
    printf("0 = FALSE, 1 = TRUE: %d\n", test);

    return 0;
}

// returns either one or zero, too lazy to define bool this time
int isIsomorphic(char* string_1, char* string_2){

    int uniques_1 = getUniques(string_1), uniques_2 = getUniques(string_2);
    int pattern1, pattern2, i;
    char a, b, c, d;

    if (uniques_1 != uniques_2) {
        return 0;
    }

    for (i = 0; i < sizeof(string_1); i++) {

        if (i == 0) {
            pattern1 = 1;
            pattern2 = 1;
            //printf("%c, %c\n", string_1[i], string_2[i]);

        }

        else {

            //printf("%c, %c, %c, %c\n", string_1[i-1], string_1[i], string_2[i-1], string_2[i]);

            if (string_1[i-1] == string_1[i]){
                pattern1++;
            }

            else {
                pattern1 = 1;
            }

            if (string_2[i-1] == string_2[i]){
                pattern2++;
            }

            else {
                pattern2 = 1;
            }


        }

        if (pattern1 != pattern2) {
            return 0;
        } 

    }

    return 1;
}

int getUniques(char* string){

    char uniques[maxsize], currentChar; 
    int alreadyInUniques;
    // for some reason length ends always being 8, dunno why 
    int length = sizeof(string), i, j, currentIndex = 0;

    for (i = 0; i < length; i++) {
        currentChar = string[i];
        alreadyInUniques = 0;  

        for (j = 0; j < (currentIndex); j++){

            if (currentChar == uniques[j]){
                alreadyInUniques = 1;
            }

        }

        if (!alreadyInUniques){
            uniques[currentIndex] = currentChar;
            currentIndex++;
        }

    }
    
    // to avoid counting nulls
    currentIndex--;

    return currentIndex;

}
