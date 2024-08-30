#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// quick custom power function

double negPow(double x, int n) {
    double product = 1;
    int i;
    for (i = 0; i < n; i++) {
        product /= x;
    }

    return product;
}

double posPow(double x, int n) {
    double product = 1;
    int i;
    for (i = 0; i < n; i++) {
        product *= x;
    }

    return product;
}

double customPow(double x, int n) {

    if (n == 0) {
        return 1;
    }

    else if (n < 0) {
        return negPow(x, -1*n);
    }

    return posPow(x, n);
}

int main(){

    double x = 6.0;
    printf("%-4.5f\n", customPow(6.0, 3));
    printf("%-4.5f\n", customPow(6.0, 0));
    printf("%-4.5f\n", customPow(6.0, -3));

    return 0;
}