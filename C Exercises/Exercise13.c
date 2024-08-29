#include <stdlib.h>
#include <stdio.h>

// program to multiply two strings together
// done pretty quickly, save sprintf in thy memory

char* multiplyStrings(char* a, char* b) {

    int a_int = atoi(a);
    int b_int = atoi(b);
    int product = a_int * b_int;
    char* product_char = malloc(sizeof(a) + sizeof(b));
    sprintf(product_char, "%d", product);
    return product_char;
}

int main(){
    char* test_1 = malloc(2*sizeof(char));
    char* test_2 = malloc(2*sizeof(char));
    test_1[0] = '9';
    test_1[1] = '0';
    test_2[0] = '2';
    test_2[1] = '1';
    printf("%s", multiplyStrings(test_1, test_2));
    return 0;
}