#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "main.h"

// need to take a look at both tie problems[resolved] and wait times[resolved]
// a bounded insertion sort to ensure that processes with a lower priority go first in the case of there being a tie in arrival time
void insertionSortForPriority(struct process** procArray, int lower, int upper) {

    int i = lower + 1, j;
    while (i < upper) {
        
        j = i;
    
        while ( (j > lower) && (procArray[j - 1]->arrival == procArray[j]->arrival) && (procArray[j - 1]->pid > procArray[j]->pid) ) {
            swap(j, j - 1, procArray);
            j--;
        }

        i++;
    }
}

// a process to update the total, which is identical to how it is elsewhere, but with one big change to response times
// and also a change to wait times to account for the process being "shuffled" back into the queue
void updateTotalRR(struct totalProcess* someTotal, int arrive, int burst, int start, int finish, int response, int prevEndTime) {


    if (someTotal->arrive == -1) {
        someTotal->arrive = arrive;
    }
    
    if (someTotal->start == -1) {
        someTotal->start = start;
    }

    someTotal->burst += burst;

    someTotal->finish = finish;

    // this has to be updated to account for processes being sat on the queue if they don't terminate after a single burst
    
    // if the prevEndTime has not been defined to a positive value, then this is the first time it has arrived in the queue
    // so just add the time from arrival to the start
    if (prevEndTime == -1) {
        someTotal->wait += (start - arrive);
    }

    // if prevEndTime has been defined, then add the gap from the prevEndTime to the next start time
    else {
        someTotal->wait += (start - prevEndTime);
    }

    someTotal->turnaround = finish - arrive;

    // function to update response when it becomes appropriate, the default of response 
    // is -1 in this simulation and only updates to a positive value when it the time has fully run down
    if ((someTotal->response == -1) && (response > 0)) {
        someTotal->response = response - arrive;
    }

}

// function to determine which processes to enqueue
int letInProcesses(struct queue* someQueue, struct process** procArray, int currentTime, int currentIndex, int length) {


    int i = currentIndex;
    bool loop = true;
    while (loop) {

        // stop once we are at array bounds
        if (i >= length) {
            loop = false;
        }

        // otherwise enqueue, and increment i
        else if (procArray[i]->arrival <= currentTime) {
            enqueue(someQueue, procArray[i]); 
            i++;
        }
        
        // if the next element in array is above current time then kill the loop
        else {
            loop = false;
        }
    }

    // i is the now the index of the next element to arrive
    return i;

}


double* rr(struct process** procArray, int length, int quantum, int numUniqueProcs) {

    // setting up a queue for processes still active, and setting up another one for processes that are completed
    struct queue* procQueue = createQueue();
    struct queue* completedQueue = createQueue();
    // holder pointer for the current process
    struct process* currentProc = (struct process*) malloc(sizeof(struct process));

    // i in this context will be used as the index for the next process to arrive
    int i = 0;

    // listing off a bunch of the vars to be printed    
    int id, arrival, burst, start, finish, wait, turnaround, respTime;

    // sorting so that lower ids arrive first in the queue in the case of two processes having the same arrival times
    insertionSortForPriority(procArray, 0, length);

    // initializing the queue
    enqueue(procQueue, procArray[0]);
    // setting the current time to the value of the arrival of the first process
    int currentTime = procArray[0]->arrival;

    struct totalProcess* totalsArray[numUniqueProcs];
    for (i = 0; i < numUniqueProcs; i++) {
        totalsArray[i] = createTotalProcess(i+1);
    }

    // resetting i, so that 1 will be the next process admitted in
    i = 1;

    // printing sequence
    printf("seq = [");

    while (!isEmpty(procQueue)) {

        // get the next process from the queue
        currentProc = dequeue(procQueue);

        // updating some variables
        id = currentProc->pid; arrival = currentProc->arrival;
        // note that burst is now set to quantum
        burst = quantum;
        start = currentTime;
        // resp time is negative so it won't update responseTime in the updateTotalRR 
        respTime = -1;
        
        // if the process isn't completed by the end of the quantum
        if (currentProc->timeRemaining - quantum > 0) {
            // update the current time by the amount of the quantum, and allow the processes in
            currentTime += quantum;
            i = letInProcesses(procQueue, procArray, currentTime, i, length);       
            // enqueue the process back into the queue
            enqueue(procQueue, currentProc);
            // update the time until response and time remaining until process is completed
            currentProc->timeTilFirstResp -= quantum; 
            currentProc->timeRemaining -= quantum;
        }

        else  {
            // doing the same, but updating by whatever amount of time 
            // less than the quantum it took for the process to complete
            currentTime += currentProc->timeRemaining;
            burst = currentProc->timeRemaining;
            i = letInProcesses(procQueue, procArray, currentTime, i, length);
            currentProc->timeTilFirstResp -= currentProc->timeRemaining;   
            currentProc->timeRemaining = 0;
            // enqueue to the completed queue this time
            enqueue(completedQueue, currentProc);
        }

        // if the process has sent a response out, update this information
        if (currentProc->timeTilFirstResp <= 0) {
            respTime = currentTime + currentProc->timeTilFirstResp;
            currentProc->hasResponded = true;
        }

        // set the finish as the current time
        finish = currentTime;

        // update the values
        updateTotalRR(totalsArray[id - 1], arrival, burst, start, finish, respTime, currentProc->prevEndTime);

        // update the previous end time to this
        currentProc->prevEndTime = currentTime;

        // print the sequence
        if (!isEmpty(procQueue)) {
            printf("%d, ", id);
        }

        else {
            printf("%d]\n", id);
        }

        // case to increment the current time in the case where the processor has to wait for a procss to arrive
        // if not all the processes are done, and the procQueue is empty
        if ((completedQueue->size < length) && (isEmpty(procQueue))) {
            while (isEmpty(procQueue)){
                // tick away the time until a process arrives
                currentTime++;
                i = letInProcesses(procQueue, procArray, currentTime, i, length);
            }
        }
        
    }

    // free the queues
    free(procQueue);
    free(completedQueue);

    return printTable(totalsArray, numUniqueProcs);
}