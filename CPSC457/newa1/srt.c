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


double getEstimatedNextBurst(int burst, double t_n, double alpha) {

    double t_next = alpha * burst + (1 - alpha) * t_n;

    return t_next;
}

void insertionSortSRT(struct process** procArray, int lower, int upper, double t_n, double alpha) {

    int i = lower + 1, j;
    while (i < upper + 1) {
        j = i;
        while ((j > lower) && (getEstimatedNextBurst(procArray[j - 1]->burstLength, t_n, alpha) > getEstimatedNextBurst(procArray[j]->burstLength, t_n, alpha) )) {
            swap(j, j - 1, procArray);
            j--;
        }
        i++;
    }
}

void srt(struct process** procArray, int length, double alpha) {

    int i;

    // listing off a bunch of the vars to be printed    
    int id, arrival, burst, start, finish, wait, turnaround, respTime;
    // defining a bunch of the values to determine averages
    double totalWaitingTime, totalTurnTime, totalRespTime;

    struct process* duplicateArray[length];
    
    copyArray(procArray, duplicateArray, length);

    int numUniqueProcs = 50;

    struct totalProcess* totalsArray[50];
    for (i = 0; i < numUniqueProcs; i++) {
        totalsArray[i] = createTotalProcess(i+1);
    }

    struct process* currentProc;
    int currentTime = procArray[0]->arrival;
    i = 0;
    double t_0 = 10;
    double t_n = t_0;
    int max = 0;

    while (i < length) {

        max = 0;
        currentProc = procArray[i];

        id = currentProc->pid; arrival = currentProc->arrival; burst = currentProc->burstLength;
        start = currentTime; finish = start + burst; wait = start - arrival; turnaround = finish - arrival; respTime = start + currentProc->timeTilFirstResp;
        
        // updating the value of t_n for each process 
        t_n = getEstimatedNextBurst(currentProc->burstLength, t_n, alpha);


        i++;

        currentTime += burst;
        
        if (max < length) {
            max = getIndexOfLastArrivedProcess(duplicateArray, currentTime, length);
        }

        insertionSort(procArray, i, max, t_n, alpha);

        // updating the values for the total processes
        updateTotal(totalsArray[id - 1], arrival, burst, start, finish, respTime);

    }

    printTable(procArray, numUniqueProcs);
}