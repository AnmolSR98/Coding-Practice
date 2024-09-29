#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "main.h"

// bounded insertion sort that sorts array by burst length, with lower ids being prioritized in the case of a tie
void insertionSortSPN(struct process** procArray, int lower, int upper) {

    int i = lower + 1, j;
    while (i < upper) {
        j = i;
        
        while ((j > lower) && (procArray[j - 1]->burstLength >= procArray[j]->burstLength)) {
            
            if ( (procArray[j - 1]->burstLength == procArray[j]->burstLength) && (procArray[j - 1]->pid > procArray[j]->pid) ) {
                swap(j, j - 1, procArray);
                j--;
            }

            else if (procArray[j - 1]->burstLength > procArray[j]->burstLength) {
                swap(j, j - 1, procArray);
                j--;
            }

            else {
                j--;
            }
        }
        i++;
    }
}

void spn(struct process** procArray, int length, int numUniqueProcs) {

    // variable to count the number of processes to be completed
    int i = 0;

    // listing off a bunch of the vars to be printed    
    int id, arrival, burst, start, finish, wait, turnaround, respTime;

    struct totalProcess* totalsArray[numUniqueProcs];
    
    for (i = 0; i < numUniqueProcs; i++) {
        totalsArray[i] = createTotalProcess(i+1);
    }

    // for the print sequence
    printf("seq = [");

    // creating a holder variable, starting the whole thing off at the exact point where the first process arrives 
    struct process* currentProc;
    int currentTime = procArray[0]->arrival;

    // a variable to keep track of which processes have come in
    int max = 0;

    // while not all of the processes are done
    i = 0;
    while (i < length) {

        // reset the value of max to 0
        max = 0;

        // read in the next process
        currentProc = procArray[i];

        // define a bunch of variables 
        id = currentProc->pid; arrival = currentProc->arrival; burst = currentProc->burstLength;
        start = currentTime; finish = start + burst; wait = start - arrival; turnaround = finish - arrival; respTime = start + currentProc->timeTilFirstResp;

        // move onto the next process
        i++;

        // updating the values for the total processes
        updateTotal(totalsArray[id - 1], arrival, burst, start, finish, respTime);

        // update the current time
        currentTime += burst;

        // printing off the sequence
        if (i < length) {
            printf("%d, ", id);
            // update the current time if there is potentially a gap between a process finishing and the next one arriving
            currentTime = maximum(currentTime, procArray[i]->arrival);
        }

        else {
            printf("%d]\n", id);
        }
        
        // if not all of the processes, have entered determine the index of the last process to have arrived
        if (max < length) {
            max = getIndexOfLastArrivedProcess(procArray, currentTime, length);
        }

        // insertion sort according to job time, simulating the sorting the ready queue by job time,
        insertionSortSPN(procArray, i, max + 1);

    }

    // print the final values
    printTable(totalsArray, numUniqueProcs);
}
