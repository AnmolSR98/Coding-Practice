#include <stdio.h>
#include "main2.h"
#define int_size 4
#define char_size 1
#define False 0
#define True 1

int main() {

    int test = 100;
    printf("%d\n", isPalindrome(test));

    return 0;
}

int isPalindrome(int x){

    if (x < 0){
        return False;
    }

    int length = 0;
    int xsim = x;

    while (xsim > 0){
        xsim = xsim / 10;
        length = length + 1;
    }

    char y[50];
    sprintf(y, "%d", x);
    int i = 0;
    int j = length - 1;


    while (i < j){
        if (y[i] != y[j]){
            return False;
        }
        i = i + 1;
        j = j - 1;
    }

    return True;
}
