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

void updateTotalRR(struct totalProcess* someTotal, int arrive, int burst, int start, int finish, int response) {


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

}

int subtractZeroFloor(int minuend, int subtrahend) {

    if (minuend - subtrahend < 0) {
        return 0;
    }

    return (minuend - subtrahend);
}

int letInProcesses(struct queue* someQueue, struct process** procArray, int currentTime, int currentIndex, int length) {

    int i = currentIndex;
    bool loop = true;
    while (loop) {

        if (i >= length) {
            loop = false;
        }

        else if (procArray[i]->arrival < currentTime) {
            enqueue(someQueue, procArray[i]); 
            i++;
        }
        
        else {
            loop = false;
        }
    }

    return i;

}


void rr(struct process** procArray, int length, int quantum) {

    // setting up a queue for processes still active, and setting up another one for processes that are completed
    struct queue* procQueue = createQueue();
    struct queue* completedQueue = createQueue();
    struct process* currentProc = (struct process*) malloc(sizeof(struct process));

    int i = 0;

    // listing off a bunch of the vars to be printed    
    int id, arrival, burst, start, finish, wait, turnaround, respTime;
    // defining a bunch of the values to determine averages
    double totalWaitingTime, totalTurnTime, totalRespTime;

    // initializing the queue
    enqueue(procQueue, procArray[0]);
    // setting the current time to the value of the arrival of the first process
    int currentTime = procArray[0]->arrival;

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

    i = 0;

    while (!isEmpty(procQueue)) {

        currentProc = dequeue(procQueue);

        id = currentProc->pid; arrival = currentProc->arrival; burst = quantum;
        start = currentTime, respTime = -1;
        
        //start = currentTime; wait = start + burst; turnaround = quantum; respTime = 0;
        
        if (currentProc->timeRemaining - quantum > 0) {
            currentTime += quantum;
            i = letInProcesses(procQueue, procArray, currentTime, i, length);       
            enqueue(procQueue, currentProc);
            currentProc->timeTilFirstResp -= quantum; 
            currentProc->timeRemaining -= quantum;
        }

        else  {
            currentTime += currentProc->timeRemaining;
            burst = currentProc->timeRemaining;
            i = letInProcesses(procQueue, procArray, currentTime, i, length);
            currentProc->timeTilFirstResp -= currentProc->timeRemaining;   
            currentProc->timeRemaining = 0;
            enqueue(completedQueue, currentProc);
        }

        if (currentProc->timeTilFirstResp <= 0) {
            respTime = currentTime + currentProc->timeTilFirstResp;
            currentProc->hasResponded = true;
        }

        finish = currentTime;

        updateTotalRR(totalsArray[id - 1], arrival, burst, start, finish, respTime);
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