#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "main.h"

// have to modify to resolve ties in id, where a few processes arrive at the same time, highest id ought to go first [DONE]

void insertionSortFCFS(struct process** procArray, int lower, int upper) {

    int i = lower + 1, j;
    while (i < upper) {
        j = i;
        // have to modify this to also sort by id in the case of a tie
        while ( (j > lower) && (procArray[j - 1]->arrival == procArray[j]->arrival) && (procArray[j - 1]->pid < procArray[j]->pid) ) {
            swap(j, j - 1, procArray);
            j--;
        }
        i++;
    }

}

void fcfs(struct process** procArray, int length) {

    int i;

    // listing off a bunch of the vars to be printed    
    int id, arrival, burst, start, finish, wait, turnaround, respTime;

    insertionSortFCFS(procArray, 0, length);

    // feeding the input array into a queue
    struct queue* procQueue = createQueue();
    for (i = 0; i < length; i++) {
        enqueue(procQueue, procArray[i]);
    }

    int numUniqueProcs = 50;

    struct totalProcess* totalsArray[numUniqueProcs];
    for (i = 0; i < numUniqueProcs; i++) {
        totalsArray[i] = createTotalProcess(i+1);
    }

    struct process* currentProc;
    int currentTime = procArray[0]->arrival;
    
    // for the print sequence
    printf("seq = [");

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

        // printing the value of the process that was just completed
        if (!isEmpty(procQueue)) {
            printf("%d, ", id);
        }

        else {
            printf("%d]\n", id);
        }
    }

    printTable(totalsArray, numUniqueProcs);
}
