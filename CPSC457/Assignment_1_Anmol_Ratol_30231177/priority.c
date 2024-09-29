#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "main.h"

// function to get 1/priority
double getPriority(struct process* someProcess) {

    return (1.0 / someProcess->pid);
}

// bounded insertion sort that sorts based on the value returned from the above function
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

// the actual priority scheduling function
void priority(struct process** procArray, int length, int numUniqueProcs) {

    // function to count the number of processes that have been completed
    int i;

    // listing off a bunch of the vars to be used for calculations  
    int id, arrival, burst, start, finish, wait, turnaround, respTime;

    // creating the totals array 
    struct totalProcess* totalsArray[numUniqueProcs];
    for (i = 0; i < numUniqueProcs; i++) {
        totalsArray[i] = createTotalProcess(i+1);
    }

    // print sequence
    printf("seq = [");

    // skipping ahead to the point where the first process arrives
    struct process* currentProc;
    int currentTime = procArray[0]->arrival;
    int max = 0;

    // need to do something in case of a gap

    // very similar to the SPN loop
    i = 0;
    while (i < length) {


        max = 0;
        
        // get the current process
        currentProc = procArray[i];

        // get a bunch of the variables needed for process calculations
        id = currentProc->pid; arrival = currentProc->arrival; burst = currentProc->burstLength;
        start = currentTime; finish = start + burst; wait = start - arrival; turnaround = finish - arrival; respTime = start + currentProc->timeTilFirstResp;

        // process has been completed
        i++;

        // move the currentTime ahead
        currentTime += burst;

        // updating the values for the total processes
        updateTotal(totalsArray[id - 1], arrival, burst, start, finish, respTime);

        // printing the sequence bit by bit
        if (i < length) {
            printf("%d, ", id);
            // update the current time if there is potentially a gap between a process finishing and the next one arriving
            currentTime = maximum(currentTime, procArray[i]->arrival);
        }

        else {
            printf("%d]\n", id);
        }
        
        // calculate what processes would have arrived in that time frame
        if (max < length) {
            max = getIndexOfLastArrivedProcess(procArray, currentTime, length);
        }

        // sort the queue by priority now
        insertionSortPriority(procArray, i, max + 1);

    }

    // print the final values
    printTable(totalsArray, numUniqueProcs);
}