#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "main.h"

// a bounded insertion sort to ensure that processes with a lower priority go first in the case of there being a tie in arrival time
void insertionSortFCFS(struct process** procArray, int lower, int upper) {

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

// the actual first come first serve function
void fcfs(struct process** procArray, int length, int numUniqueProcs) {

    // i to count the number of processes that have been read in
    int i;

    // variables to be used in calculations later on   
    int id, arrival, burst, start, finish, wait, turnaround, respTime;

    // sorting the array
    insertionSortFCFS(procArray, 0, length);

    // feeding the input array into a queue
    struct queue* procQueue = createQueue();
    for (i = 0; i < length; i++) {
        enqueue(procQueue, procArray[i]);
    }

    // creating a queue of completed processes
    struct queue* completedQueue = createQueue();

    // creating a bunch of totalProcesses, which contains the information for each id
    struct totalProcess* totalsArray[numUniqueProcs];
    for (i = 0; i < numUniqueProcs; i++) {
        totalsArray[i] = createTotalProcess(i+1);
    }

    // start the simulation off at the point where the first 
    struct process* currentProc;
    int currentTime = procArray[0]->arrival;
    
    // for the print sequence
    printf("seq = [");

    while (!isEmpty(procQueue)) {

        // simulating getting the next process from the queue
        currentProc = dequeue(procQueue);

        // getting the currentTime (accounting for the case where there is a gap in between a process finishing, and the next one arriving)
        currentTime = maximum(currentTime, currentProc->arrival);
        
        // getting its attributes
        id = currentProc->pid; arrival = currentProc->arrival; burst = currentProc->burstLength;

        // using those to make some calculations on the process
        start = currentTime; finish = start + burst; wait = start - arrival; turnaround = finish - arrival; respTime = start + currentProc->timeTilFirstResp;

        // updating the values for the total processes
        updateTotal(totalsArray[id - 1], arrival, burst, start, finish, respTime);

        // updating the current time
        currentTime += burst;

        // printing the value of the process that was just completed
        if (!isEmpty(procQueue)) {
            printf("%d, ", id);
        }

        else {
            printf("%d]\n", id);
        }

    }

    // printing off the 50 line table that contains a summary of each process
    printTable(totalsArray, numUniqueProcs);
}

