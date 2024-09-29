#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "main.h"

#include "fcfs.c"
#include "spn.c"
#include "rr.c"
#include "priority.c"
#include "srt.c"

#define buffer 64
#define numAttr 4
#define expectedLength 16
#define pid_column 0
#define arr_column 1
#define tim_column 2
#define bur_column 3

void printArray(double* someArray, int length) {
    printf("[ ");
    int i = 0;
    for (i = 0; i < length; i++) {

        if (i != length - 1) {
            printf("%10.5f, ", someArray[i]);
        }

        else {
            printf("%10.5f]\n", someArray[i]);
        }
    }


}

int main(int argc, char** argv) {

    // most crucial thing right now is to get the number of lines in an input file
    // PROCESSES ARE BEING READ IN CORRECTLY 
    // maybe use feof to determine end of file

    // https://stackoverflow.com/questions/12911299/read-csv-file-in-c
    // perhaps change to another name otherwise it may not work properly when TA has to run[]
    int length = 1000; int numUniqueProcs = 50; int extraIn;
    char* procType; char* inputArr; 

    /** 
    // have to change to account for the fact that rr and srt take an additional argument in
    if ( ( (strcmp(argv[1], "rr") == 0) || (strcmp(argv[1], "srt") == 0) ) ) {
        
        if (argc != 4) {
            printf("Incorrect number of input arguments given!\n");
            return 0;
        }

        extraIn = atoi(argv[2]);
        procType = argv[1];
        inputArr = argv[3];

    }

    else if (argc != 3) {
        printf("Incorrect number of input arguments given!\n");
        return 0;
    }

    else {
        procType = argv[1];
        inputArr = argv[2];
    }**/

   inputArr = "input.csv";
   procType = "srt";
   

    // actual input file
    FILE* inputCSV = fopen(inputArr, "r");
    // array of pointers to processes
    struct process* processArray[length];
    // ie an array to temporarily hold each string before it is converted to an 
    char inputString[buffer];
    // array to hold the strings from cycler, which are then passed on the createProcess
    char holderArray[numAttr][expectedLength]; 
    // an array to run for as many lines are in the input file
    int i = 0;
    // fgets seems to divy it up by \n anyways, run a for loop here
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

    if (strcmp(procType, "rr") == 0) {
        
        rr(processArray, length, 1, numUniqueProcs);
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

    // change this one too later, change it to SRT once correctly implemented
    else if (strcmp(procType, "srt") == 0) {

        srt(processArray, length, numUniqueProcs, 0.5);

        /** 
        double waitTimes[11];
        double turnTimes[11];
        double respTimes[11];
        double* latestSRT = malloc(sizeof(double) * 3);

        double alpha = 0.0;

        int i = 0;
        for (alpha = 0.0; alpha <= 1.0; alpha += 0.1) {
            latestSRT = srt(processArray, length, alpha); 
            waitTimes[i] = latestSRT[0];
            turnTimes[i] = latestSRT[1];
            respTimes[i] = latestSRT[2];

            i++;
        }

        printArray(waitTimes, 11);
        printArray(turnTimes, 11);
        printArray(respTimes, 11);*/
    }

    return 0;
}
