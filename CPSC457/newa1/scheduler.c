#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "main.h"

// including the other c files
#include "fcfs.c"
#include "spn.c"
#include "rr.c"
#include "priority.c"
#include "srt.c"

// a bunch of variables with regards to the csv that is to be read in
#define buffer 64
#define numAttr 4
#define expectedLength 16
#define pid_column 0
#define arr_column 1
#define tim_column 2
#define bur_column 3


int main(int argc, char** argv) {
    
    // some variables to hold data, and the number of lines in the input file and the num of unique processes
    int length = 1000; int numUniqueProcs = 50; double extraIn;
    char* procType; char* inputArr; 

    // statement to handle for round robin and shortest remaining time calls
    if ( ( (strcmp(argv[1], "rr") == 0) || (strcmp(argv[1], "srt") == 0) ) ) {
        
        // error handling for the above two types
        if (argc != 4) {
            printf("Incorrect number of input arguments given! Correct format is: ./scheduler processType parameter inputfile!\n");
            return 0;
        }

        // 
        extraIn = atof(argv[2]);
        procType = argv[1];
        inputArr = argv[3];

    }

    // error handling for the other 3 types
    else if (argc != 3) {
        printf("Incorrect number of input arguments given! Correct format is: ./scheduler processType inputfile!\n\n");
        return 0;
    }

    // statements for the other 3 types
    else {
        procType = argv[1];
        inputArr = argv[2];
    }

   /** 
   procType = "srt";
   inputArr = "input.csv";
   double alpha = 0.5;
   */

    // the following snippet of lines, until the fclose statement borrow heavily from this page on stack overflow: // https://stackoverflow.com/questions/12911299/read-csv-file-in-c

    // opening input file
    FILE* inputCSV = fopen(inputArr, "r");
    // array of pointers to processes
    struct process* processArray[length];
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
        strcpy(holderArray[pid_column], strtok(inputString, ","));
        strcpy(holderArray[arr_column], strtok(NULL, ","));
        strcpy(holderArray[tim_column], strtok(NULL, ","));
        strcpy(holderArray[bur_column], strtok(NULL, ","));

        // adds them provided we are past the first line, so the text won't be added as an entry
        if (i > 0) {
            processArray[i - 1] = createProcess(holderArray[pid_column], holderArray[arr_column], holderArray[tim_column], holderArray[bur_column]);
        }

        // continue on through the lines
        i++;
    }

    // closing the input csv
    fclose(inputCSV);

    // if else statements to run the chosen simulator
    if (strcmp(procType, "rr") == 0) {

        // extra in being the potential optional parameter given
        int quantum = extraIn;

        rr(processArray, length, quantum, numUniqueProcs);
    } 

    else if (strcmp(procType, "fcfs") == 0) {
        fcfs(processArray,  length, numUniqueProcs);
    }

    else if (strcmp(procType, "spn") == 0) {
        spn(processArray,  length, numUniqueProcs);
    }

    else if (strcmp(procType, "priority") == 0) {
        priority(processArray,  length, numUniqueProcs);
    }

    else if (strcmp(procType, "srt") == 0) {

        // extra in being the potential optional parameter given
        double alpha = extraIn;

        // some error handling for alpha
        if ((alpha < 0) || (alpha > 1.0)) {
            printf("Enter an alpha value between 0.0 and 1.0, in increments of 0.1!\n");
        }

        srt(processArray, length, numUniqueProcs, alpha);

    }

    return 0;
}
