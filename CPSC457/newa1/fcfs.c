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

void fcfs(struct process** procArray, int length) {

    int i;

    // listing off a bunch of the vars to be printed    
    int id, arrival, burst, start, finish, wait, turnaround, respTime;
    // defining a bunch of the values to determine averages
    float totalWaitingTime, totalTurnTime, totalRespTime;

    // feeding the input array into a queue
    struct queue* procQueue = createQueue();
    for (i = 0; i < length; i++) {
        enqueue(procQueue, procArray[i]);
    }

    int numUniqueProcs = 50;

    struct totalProcess* totalsArray[50];
    for (i = 0; i < numUniqueProcs; i++) {
        totalsArray[i] = createTotalProcess(i+1);
    }

    // printing the initial sequence
    printSequence(procArray, length);
    printf("\n");

    // printing the first line of the table
    printf(firstLine);

    struct process* currentProc;
    int currentTime = procArray[0]->arrival;

    while (!isEmpty(procQueue)) {

        // simulating getting the next process from the queue
        currentProc = dequeue(procQueue);
        
        // getting its attributes
        id = currentProc->pid; arrival = currentProc->arrival; burst = currentProc->burstLength;

        // using those to make some calculations on the process
        start = currentTime; finish = start + burst; wait = start - arrival; turnaround = finish - arrival; respTime = start + currentProc->timeTilFirstResp;

        // updating the values for the total processes
        updateTotal(totalsArray[id - 1], arrival, burst, start, finish, respTime);

        // updating the current time
        currentTime += burst;
    }

    struct totalProcess* currentTotal = (struct totalProcess*) malloc(sizeof(struct totalProcess));
    for (i = 0; i < numUniqueProcs; i++) {
        // printing off a new column
        currentTotal = totalsArray[i];
        // updating the totals
        totalWaitingTime += currentTotal->wait; totalTurnTime += currentTotal->turnaround; totalRespTime += currentTotal->response;
        printf(standard, currentTotal->pid, currentTotal->arrive, currentTotal->burst, currentTotal->start, currentTotal->finish, currentTotal->wait, currentTotal->turnaround, currentTotal->response);
    }

    // converting these to the averages, ought to update the variable names
    totalWaitingTime /= numUniqueProcs; totalTurnTime /= numUniqueProcs; totalRespTime /= numUniqueProcs;

    printf(finalThree, totalWaitingTime, totalTurnTime, totalRespTime);
}

