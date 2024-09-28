#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "main.h"

void insertionSortSPN(struct process** procArray, int lower, int upper) {

    int i = lower + 1, j;
    while (i < upper) {
        j = i;
        // have to modify this to also sort by id in the case of a tie [DONE]
        while ((j > lower) && (procArray[j - 1]->burstLength >= procArray[j]->burstLength)) {
            
            if ( (procArray[j - 1]->burstLength == procArray[j]->burstLength) && (procArray[j - 1]->pid < procArray[j]->pid) ) {
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

void spn(struct process** procArray, int length) {

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

    // for the print sequence
    printf("seq = [");

    struct process* currentProc;
    int currentTime = procArray[0]->arrival;
    i = 0;
    int max = 0;

    // some sort of bug with response times

    while (i < length) {

        max = 0;
        currentProc = procArray[i];

        id = currentProc->pid; arrival = currentProc->arrival; burst = currentProc->burstLength;
        start = currentTime; finish = start + burst; wait = start - arrival; turnaround = finish - arrival; respTime = start + currentProc->timeTilFirstResp;

        i++;

        currentTime += burst;
        
        // note to self, max returns the index of the next process that hasnt arrived yet, maybe opt to rename it, fixed now
        if (max < length) {
            max = getIndexOfLastArrivedProcess(duplicateArray, currentTime, length);
        }

        insertionSortSPN(procArray, i, max + 1);

        // updating the values for the total processes
        updateTotal(totalsArray[id - 1], arrival, burst, start, finish, respTime);

        if (i < length) {
            printf("%d, ", id);
        }

        else {
            printf("%d]\n", id);
        }

    }

    printTable(totalsArray, numUniqueProcs);
}
