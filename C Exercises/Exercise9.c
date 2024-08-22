#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// designing own atoi function

bool isDigit(char someChar) {
    if (someChar == '1') {return true;}
    else if (someChar == '2') {return true;}
    else if (someChar == '3') {return true;}
    else if (someChar == '4') {return true;}
    else if (someChar == '5') {return true;}
    else if (someChar == '6') {return true;}
    else if (someChar == '7') {return true;}
    else if (someChar == '8') {return true;}
    else if (someChar == '9') {return true;}
    else if (someChar == '0') {return true;}
    else {return false;}
}

int getNumFromChar(char someChar){

    if (someChar == '1') {return 1;}
    else if (someChar == '2') {return 2;}
    else if (someChar == '3') {return 3;}
    else if (someChar == '4') {return 4;}
    else if (someChar == '5') {return 5;}
    else if (someChar == '6') {return 6;}
    else if (someChar == '7') {return 7;}
    else if (someChar == '8') {return 8;}
    else if (someChar == '9') {return 9;}
    else if (someChar == '0') {return 0;}
    else {return (-1);}

}

int myAtoi(char* s){

    int length = sizeof(s);
    int i;
    int value = 0;
    bool isPositive;
    bool isLeading = true;
    printf("%d\n", length);

    // issue where it is not reading the end of the string
    for (i = 0; i < length; i++) {

        if (isDigit(s[i])){
            printf("1\n");
            isLeading = false;
            value = value*10 + getNumFromChar(s[i]);
        }

        else if ((s[i] == ' ') && (isLeading)){
            printf("2\n");
            isLeading = true;
        }

        else if ((s[i] == '+') && (isLeading)) {
            printf("3\n");
            isPositive = true;
        }

        else if ((s[i] == '-') && (isLeading)) {
            printf("4\n");
            isPositive = false;
        }

        else if (s[i] == (char)0){
            printf("5\n");
        }

        else {
            printf("6\n");
            return 0;
        }

    }

    if (isPositive){
        return value;
    }

    else {
        return (-1 * value);
    }

}

int main(){
    char test[6] = "  +542";
    printf("%d\n", myAtoi((char*)test));
    return 0;
}