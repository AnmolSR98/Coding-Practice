// importing a bunch of standard c stuff
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// including the other algorithms
#include "main.h"
#include "fifo.c"
#include "lru.c"
#include "optimal.c"
#include "secondchance.c"

// defining a bunch of variables to be used
#define length 15000
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
void runLoopOPT(page** listOPages){
    
    int i, y, z;
    int* holderArray = (int*) malloc(sizeof(int)*2);
    printf("OPT\n");
    printHeader();
    for (i = 1; i <= 100; i++) {
        holderArray = optimal(listOPages, i, length);
        printData(i, holderArray[0], holderArray[1]);
    }
    printFooter();
}

void runLoopLRU(page** listOPages){
    
    int i, y, z;
    int* holderArray = (int*) malloc(sizeof(int)*2);
    printf("LRU\n");
    printHeader();
    for (i = 1; i <= 100; i++) {
        holderArray = lru(listOPages, i, length);
        printData(i, holderArray[0], holderArray[1]);
    }
    printFooter();
}

void runLoopFIFO(page** listOPages){
    
    int i, y, z;
    int* holderArray = (int*) malloc(sizeof(int)*2);
    printf("FIFO\n");
    printHeader();
    for (i = 1; i <= 100; i++) {
        holderArray = fifo(listOPages, i, length);
        printData(i, holderArray[0], holderArray[1]);
    }
    printFooter();
}

void runLoopCLK(page** listOPages, int numUniquePages){
    
    int m, n, y, z;
    int numFrames = 25;
    int* holderArray = (int*) malloc(sizeof(int)*2);
    
    printf("CLK\n");

    m = 10;
    // setting the loop for m = 10, n from 1 to 32
    printClockHeaderN();
    for (n = 1; n <= 32; n++) {
        holderArray = secondChance(listOPages, numFrames, numUniquePages, m, n, length);
        printClockData(n, holderArray[0], holderArray[1]);
    }
    printFooter();
    printf("\n");

    n = 8;
    // setting the loop for n = 10, n from 1 to 32
    printClockHeaderM();
    for (m = 1; m <= 100; m++) {
        holderArray = secondChance(listOPages, numFrames, numUniquePages, m, n, length);
        printClockData(m, holderArray[0], holderArray[1]);
    }
    printFooter();
}

int main (int argc, char** argv) {

    char* method; 
    char* filename;

    if (argc != 3) {
        printf("The correct format is: <./pageReplacement method filename>!");
        return 0;
    }

    else {
        method = argv[1];
        filename = argv[2];
    }

    // reading in the pages to be used later
    page** listOPages = (page**) malloc(sizeof(page) * length);
    listOPages = readIn(filename);
    int numUniquePages = 500;
    
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

    else {
        printf("Enter a valid method (one of: FIFO, LRU, OPT, CLK)!");
    }

    return 0;
}