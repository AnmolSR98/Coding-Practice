#include <stdio.h>
#include <stdlib.h>

// simple function to get averages of an input array of doubles
double getAverage(double* someArr, int length) {

    double total = 0.0;
    int i = 0;
    for (i = 0; i < length; i++) {
        total += someArr[i];
    }

    return (double) (total / length);
}