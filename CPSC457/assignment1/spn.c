#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "main.h"
#include "heap.c"
#define buffer 64
#define numAttr 4
#define expectedLength 16
#define pid_column 0
#define arr_column 1
#define tim_column 2
#define bur_column 3


// going to have to use a heap sort first

void spn(struct process** procArray, int length) {

    // all of these are in milliseconds
    char* firstLine = "Id, Arrival, Burst, Start, Finish, Wait, Turnaround, Response Time\n";
    char* standard =  "%2d, %7d, %5d, %5d, %6d, %4d, %10d, %13d\n";
    char* finalThree ="Average waiting time: %5.2f\nAverage turnaround time: %5.2f\nAverage response time: %5.2f\n";
    int i;

    // listing off a bunch of the vars to be printed    
    int id, arrival, burst, start, finish, wait, turnaround, respTime;
    // defining a bunch of the values to determine averages
    float totalWaitingTime, totalTurnTime, totalRespTime;

    //INSERT SORTING ALGORITHM HERE
    struct heap* procHeap = createHeap(length);

    printSequence(procArray, length);
    printf("\n");

    for (i = 0; i < length; i++) {
        addProc(procArray[i], procHeap);
    }

    printSequence(procHeap->someArray, length);
    printf("\n");

    for (i = 0; i < length; i++) {
        procArray[i] = pop(procHeap);
    }

    i = 0;

    // printing the initial sequence
    printSequence(procArray, length);
    printf("\n");

    printSequence(procHeap->someArray, length);
    printf("\n");

    // printing the first line of the table
    printf(firstLine);

    i = length;
    while (i < length) {

        id = procArray[i]->pid; arrival = procArray[i]->arrival; burst = procArray[i]->burstLength;
        start = arrival; finish = arrival + burst; wait = 0; turnaround = burst; respTime = 0;

        totalWaitingTime += wait; totalTurnTime += turnaround; totalRespTime += respTime;

        printf(standard, id, arrival, burst, start, finish, wait, turnaround, respTime);

        i++;
    }

    // converting these to the averages, ought to update the variable names
    totalWaitingTime /= length; totalTurnTime /= length; totalRespTime /= length;

    printf(finalThree, totalWaitingTime, totalTurnTime, totalRespTime);
}

int main() {

    // most crucial thing right now is to get the number of lines in an input file
    // PROCESSES ARE BEING READ IN CORRECTLY 
    // maybe use feof to determine end of file

    // https://stackoverflow.com/questions/12911299/read-csv-file-in-c
    // perhaps change to another name otherwise it may not work properly when TA has to run[]
    
    // actual input file
    FILE* inputCSV = fopen("input.csv", "r");
    // array of pointers to processes
    struct process* processArray[1000];
    // ie an array to temporarily hold each string before it is converted to an 
    char inputString[buffer];
    // array to hold the strings from cycler, which are then passed on the createProcess
    char holderArray[numAttr][expectedLength]; 
    // an array to run for as many lines are in the input file
    int i = 0;
    // fgets seems to divy it up by \n anyways, run a for loop here
    while (i < 1001) {
        
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

    int test = 999;
    printf("The id of process %d is: %d\n", test, processArray[test]->pid);

    // closing the input csv
    fclose(inputCSV);

    // working well enough
    //fcfs(processArray, 1000);

    spn(processArray, 1000);

    return 0;
}