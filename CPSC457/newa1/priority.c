#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "main.h"
#define buffer 64
#define numAttr 4
#define expectedLength 16
#define pid_column 0
#define arr_column 1
#define tim_column 2
#define bur_column 3

double getPriority(struct process* someProcess) {
    double priority = 1.0 / someProcess->pid;
    return (1.0 / someProcess->pid);
}

void insertionSortPriority(struct process** procArray, int lower, int upper) {

    int i = lower + 1, j;
    while (i < upper) {
        j = i;
        while ((j > lower) && (getPriority(procArray[j - 1]) > getPriority(procArray[j]))) {
            swap(j, j - 1, procArray);
            j--;
        }
        i++;
    }
}


void priority(struct process** procArray, int length) {

    int i;

    // listing off a bunch of the vars to be printed    
    int id, arrival, burst, start, finish, wait, turnaround, respTime;

    struct process* duplicateArray[1000];
    copyArray(procArray, duplicateArray, 1000);

    int numUniqueProcs = 50;

    struct totalProcess* totalsArray[50];
    for (i = 0; i < numUniqueProcs; i++) {
        totalsArray[i] = createTotalProcess(i+1);
    }

    printf("seq = [");

    struct process* currentProc;
    int currentTime = procArray[0]->arrival;
    int max = 0;
    i = 0;

    // bug where this prints a 45 at the very end for some reason, need to fix
    while (i < length) {

        max = 0;
        currentProc = procArray[i];

        id = currentProc->pid; arrival = currentProc->arrival; burst = currentProc->burstLength;
        start = currentTime; finish = start + burst; wait = start - arrival; turnaround = finish - arrival; respTime = start + currentProc->timeTilFirstResp;

        i++;

        currentTime += burst;
        

        if (max < length) {
            max = getIndexOfLastArrivedProcess(duplicateArray, currentTime, length);
        }

        insertionSortPriority(procArray, i, max);

        // updating the values for the total processes
        updateTotal(totalsArray[id - 1], arrival, burst, start, finish, respTime);

        // printing the sequence bit by bit
        if (i < length) {
            printf("%d, ", id);
        }

        else {
            printf("%d]\n", id);
        }
    }

    printTable(totalsArray, numUniqueProcs);
}