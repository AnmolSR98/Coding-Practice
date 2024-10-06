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
page** readIn() {

    char* inputFile = "input.csv";

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

void runLoop(page** listOPages){
    
    int i, y, z;
    int* holderArray = (int*) malloc(sizeof(int)*2);
    printHeader();
    for (i = 1; i <= 100; i++) {
        holderArray = optimal(listOPages, i, length);
        printData(i, holderArray[0], holderArray[1]);
    }
    printFooter();
}

int main () {

    // reading in the pages to be used later
    page** listOPages = (page**) malloc(sizeof(page) * length);
    listOPages = readIn();
    
    //lru(listOPages, 50, length);
    //optimal(listOPages, 50, length);

    int i;
    int* holderArray = (int*) malloc(sizeof(int)*2);
    printHeader();
    for (i = 1; i <= 1; i++) {
        holderArray = secondChance(listOPages, 25, length, 8, 8, 500);
        //printData(i, holderArray[0], holderArray[1]);
    }
    //printFooter();

    return 0;
}