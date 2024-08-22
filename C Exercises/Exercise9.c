#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

// designing own atoi function [COMPLETED]

bool isDigit(char someChar) {

    bool isDigit = false;

    switch(someChar){
        case '1': isDigit = true; break;
        case '2': isDigit = true; break;
        case '3': isDigit = true; break;
        case '4': isDigit = true; break;
        case '5': isDigit = true; break;
        case '6': isDigit = true; break;
        case '7': isDigit = true; break;
        case '8': isDigit = true; break;
        case '9': isDigit = true; break;
        case '0': isDigit = true; break;
    }

    return isDigit;
}

int getNumFromChar(char someChar){

    int num = 0;

    switch(someChar){
        case '1': num = 1; break;
        case '2': num = 2; break;            
        case '3': num = 3; break;
        case '4': num = 4; break;
        case '5': num = 5; break;
        case '6': num = 6; break;
        case '7': num = 7; break;
        case '8': num = 8; break;
        case '9': num = 9; break;
    }

    return num;
}

int myAtoi(char* s){

    int i = 0;
    int value = 0;
    bool isPositive = true;
    bool isLeading = true;
    bool hasNegativeSign = false;

    // issue where it is not reading the end of the string, started using -96 to represent a null terminator in a char array
    while (s[i] != -96) {
        
        // if digit, add it to the current value
        if (isDigit(s[i])){
            isLeading = false;
            value = value*10 + getNumFromChar(s[i]);
        }

        // bunch of statements
        // to read past whitespace
        else if ((s[i] == ' ') && (isLeading)){
            isLeading = true;
        }

        // checking for signs
        else if ((s[i] == '+') && (isLeading)) {
            isLeading = false;
            isPositive = true;
        }

        else if ((s[i] == '-') && (isLeading)) {
            isLeading = false;
            isPositive = false;
            hasNegativeSign = true;
        }

        // read past ending whitespace
        else if ((s[i] == ' ') && (!isLeading)){} 

        else if (s[i] == 0) {}

        else {
            return 0;
        }

        i++;
    }           

    // making these numbers the appropriate sign
    if (isPositive){
        return value;
    }

    else {
        return (-1 * value);
    }

}

int main(){
    char test1[5] = "542";
    printf("Value of inputted string is: %d\n", myAtoi(test1));

    return 0;
}