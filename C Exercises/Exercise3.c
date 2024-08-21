#include <stdio.h>
#include <math.h>
#include "main3.h"

int main() {

    double test = mySqrt(8.0);

    printf("%.10f\n", test);

    return 0;
}

double mySqrt(double x){
    
    double immVar = 1;
    double sum = 0;
    double i = 0;
    double log_x = log(x);

    while (immVar > 0.0000000001){

        sum = sum + immVar;
        i = i + 1;
        immVar = (immVar * 0.5);
        immVar = (immVar * log_x);
        immVar = (immVar / i);
    }

    return sum;

}
