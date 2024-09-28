#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "main.h"

double updateExponentialAverage(double burst, double T_n, double alpha) {

    double t_next = alpha * burst + (1 - alpha) * T_n;

    return t_next;
}

void updateTotalSRT(struct totalProcess* someTotal, int arrive, int totalBurst, int burst, int start, int finish, int response, double alpha) {


    if (someTotal->arrive == -1) {
        someTotal->arrive = arrive;
    }
    
    if (someTotal->start == -1) {
        someTotal->start = start;
    }

    someTotal->burst += burst;

    someTotal->finish = finish;

    // this has to be updated to account for processes being sat on the wait for much longer, will almost certainly involve using
    // the previous end time 
    someTotal->wait = finish - arrive - burst;

    someTotal->turnaround = finish - arrive;

    if ((someTotal->response == -1) && (response > 0)) {
        someTotal->response = response - arrive;
    }

    // if the prev burst value is uninitialized, update it
    if (someTotal->prevBurst == -1) {
        someTotal->prevBurst = totalBurst;
        someTotal->actualRemainingTime = totalBurst;
    }

    // updating the total value
    someTotal->estimatedRemainingTime -= burst;
    someTotal->actualRemainingTime -= burst;

    // checking that if the estimatedRemainingTime equals zero, we recalculate the estimated average
    if (someTotal->actualRemainingTime == 0) {
        someTotal->exponentialAverage = updateExponentialAverage(someTotal->prevBurst, someTotal->exponentialAverage, alpha);
        someTotal->estimatedRemainingTime = someTotal->exponentialAverage;
        // set someTotal->prevBurst to -1 to indicate that it has been uninitialized, so that the if statement will be triggered the next
        // time it comes up at the head of the ready queue.
        someTotal->prevBurst = -1;
    }

}

void insertionSortSRT(struct process** procArray, struct totalProcess** totalsArray, int lower, int upper) {

    int i = lower + 1, j;
    while (i < upper) {
        j = i;
        while ((j > lower) && (totalsArray[procArray[j - 1]->pid - 1]->estimatedRemainingTime > totalsArray[procArray[j]->pid - 1]->estimatedRemainingTime)) {
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
    
    double T_0 = 10;

    struct totalProcess* totalsArray[50];
    for (i = 0; i < numUniqueProcs; i++) {
        totalsArray[i] = createTotalProcess(i+1);
        // this is not entirely accurate, but am simply initializing the estimated remaining time and exponential average
        // as the t_n
        totalsArray[i]->exponentialAverage = T_0;
        totalsArray[i]->estimatedRemainingTime = T_0;
    }

    struct process* currentProc;
    int currentTime = procArray[0]->arrival;
    i = 0;
    double T_next = T_0;
    int max = 0;

    // step to define the minimum amount of time that currentTime can step forward by
    int step = 1;

    // printing the sequence
    printf("seq = [");

    // going to have to increment this so that it goes up by 1, also simulate waiting in the case of no processes arriving for the other ones
    while (i < length) {

        max = 0;
        currentProc = procArray[i];

        id = currentProc->pid; arrival = currentProc->arrival; burst = step;
        start = currentTime; finish = start + burst; wait = start - arrival; turnaround = finish - arrival; respTime = start + currentProc->timeTilFirstResp;
        
        // incrementing the currentTime by the step 
        currentTime += step;

        updateTotalSRT(totalsArray[id - 1], arrival, currentProc->burstLength, burst, start, finish, respTime, alpha);

        if (totalsArray[id - 1]->actualRemainingTime == 0) {
            i++;
        }
        
        if (max < length) {
            max = getIndexOfLastArrivedProcess(duplicateArray, currentTime, length);
        }

        // in this case, we want to include the lowest index, since it may not have actually terminated yet
        insertionSortSRT(procArray, totalsArray, i, max + 1);
        

        if (i < length) {
            printf("%d, ", id);
        }

        else {
            printf("%d]\n", id);
        }
    }

    printTable(totalsArray, numUniqueProcs);
}