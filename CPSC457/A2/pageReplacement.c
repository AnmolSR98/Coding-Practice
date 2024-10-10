// importing a bunch of standard c stuff, if needed
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// including the other files to be used
#include "main.h"
#include "fifo.c"
#include "lru.c"
#include "optimal.c"
#include "secondchance.c"

// defining a bunch of variables to be used for reading in the csv file
// csv actually contains slightly more than 15000 lines of data to read in
#define length 15050
#define buffer 64
#define numAttr 2
#define expectedLength 16
#define no_column 0
#define di_column 1

// function to read in csv file
page** readIn(char* inputFile) {

    // array of page pointers
    page** pageArray = (page**) malloc(length*sizeof(page));

    // opening input file
    FILE* inputCSV = fopen(inputFile, "r");
    // ie an array to temporarily hold each string before it is converted to a process
    char inputString[buffer];
    // array to hold the strings from cycler, which are then passed on the createProcess
    char holderArray[numAttr][expectedLength]; 
    // to keep track of what line we are at
    int i = 0;
    while (i < length + 1) {
        
        // reads in lines from csv line by line
        fgets(inputString, buffer, inputCSV);
        // using strtok to cycle through the various process attributes
        strcpy(holderArray[no_column], strtok(inputString, ","));
        strcpy(holderArray[di_column], strtok(NULL, ","));

        // adds them provided we are past the first line, so the text won't be added as an entry
        if (i > 0) {
            pageArray[i - 1] = createPage(holderArray[no_column], holderArray[di_column]);
        }

        // continue on through the lines
        i++;
    }

    // closing the input csv
    fclose(inputCSV);

    return pageArray;

}

// bunch of generic functions to run loops for the various page replacement algorithms

// this one is for optimal
void runLoopOPT(page** listOPages){
    
    int i, y, z;
    int* holderArray = (int*) malloc(sizeof(int)*2);
    printf("OPT\n");
    printHeader();
    for (i = 1; i <= 100; i++) {
        holderArray = optimal(listOPages, i, length);
        //printData(i, holderArray[0], holderArray[1]);
        printf("%d, %d, %d\n", i, holderArray[0], holderArray[1]);
    }
    printFooter();
}

// lru function
void runLoopLRU(page** listOPages){
    
    int i, y, z;
    int* holderArray = (int*) malloc(sizeof(int)*2);
    printf("LRU\n");
    printHeader();
    for (i = 1; i <= 100; i++) {
        holderArray = lru(listOPages, i, length);
        //printData(i, holderArray[0], holderArray[1]);
        printf("%d, %d, %d\n", i, holderArray[0], holderArray[1]);
    }
    printFooter();
}

// fifo function
void runLoopFIFO(page** listOPages){
    
    int i, y, z;
    int* holderArray = (int*) malloc(sizeof(int)*2);
    printf("FIFO\n");
    printHeader();
    for (i = 1; i <= 100; i++) {
        holderArray = fifo(listOPages, i, length);
        //printData(i, holderArray[0], holderArray[1]);
        printf("%d, %d, %d\n", i, holderArray[0], holderArray[1]);
    }
    printFooter();
}

// finally, one for second chance/clock
void runLoopCLK(page** listOPages, int numUniquePages){
    
    int m, n, y, z;
    int numFrames = 25;
    int* holderArray = (int*) malloc(sizeof(int)*2);
    
    printf("CLK\n");

    m = 10;
    // setting the loop for m = 10, n from 1 to 32
    printClockHeaderN();
    for (n = 1; n <= 32; n++) {
        holderArray = secondChance(listOPages, numFrames, length, m, n, numUniquePages);
        //printClockData(n, holderArray[0], holderArray[1]);
        printf("%d, %d, %d\n", n, holderArray[0], holderArray[1]);
    }
    printClockFooter();
    printf("\n");

    n = 8;
    // setting the loop for n = 10, n from 1 to 32
    printClockHeaderM();
    for (m = 1; m <= 100; m++) {
        holderArray = secondChance(listOPages, numFrames, length, m, n, numUniquePages);
        //printClockData(m, holderArray[0], holderArray[1]);
        printf("%d, %d, %d\n", m , holderArray[0], holderArray[1]);
    }
    printClockFooter();
}

int main (int argc, char** argv) {

    // variables to hold both the method and filename
    char* method; 
    char* filename;

    // checking that the correct format for the input string was used, print an error message if not
    if (argc != 3) {
        printf("The correct format is: <./pageReplacement method filename>!");
        return 0;
    }

    else {
        // otherwise assign those strings to method and filename
        method = argv[1];
        filename = argv[2];
    }



    // reading in the pages to be used later
    page** listOPages = (page**) malloc(sizeof(page) * length);
    listOPages = readIn("input.csv");
    int numUniquePages = 500;
     
    // if else statements to run selected loop
    if (strcmp(method, "FIFO") == 0) {
        runLoopFIFO(listOPages);
    }

    else if (strcmp(method, "LRU") == 0) {
        runLoopLRU(listOPages);
    }
    
    else if (strcmp(method, "OPT") == 0) {
        runLoopOPT(listOPages);
    }
    
    else if (strcmp(method, "CLK") == 0) {
        runLoopCLK(listOPages, numUniquePages);
    }

    // if no valid method was given, print an error message
    else {
        printf("Enter a valid method (one of: FIFO, LRU, OPT, CLK)!");
    } 

    return 0;
}