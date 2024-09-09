#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

int power(int base, int exponent) {
    
    int i, product = 1;
    for (i = 1; i <= exponent; i++) {
        product *= base; 
    }

    return product;
}

// custom function to get integer value of log10(number)
int logTen(int number) {

    int i = 0;
    while (number > 0) {
        number /= 10;
        i++;
    }

    return (i - 1);
}

// factorial function
int factorial(int n) {
    
    int i, product = 1;
    for (i = 1; i <= n; i++) {
        product *= i;
    }

    return product;
}

// get digits at position
int getDigitAtPosition(int position, int number) {

    if (position > logTen(number) + 1) {
        return 0;
    }

    int valuesHigher = (number / power(10, position)) * power(10, position);

    number = number - valuesHigher;

    if (number == 0) {
        return 0;
    }
    
    number = (int) number / power(10, logTen(number)); 


    return number;
}

int getFactorialZeroes(int n) {

    int fact = factorial(n);
    int i = 1;
    bool loop = true;
    while (loop) {
        
        if (getDigitAtPosition(i, fact) == 0) {
            i++;
        } 

        else {
            return (i - 1);
        }
    }

}

int main() {

    int numZeroes = getFactorialZeroes(10);

    return 0;
}