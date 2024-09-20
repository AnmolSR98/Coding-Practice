#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "main.h"

void printSequence(struct process** procArray, int length) {

    printf("seq = [ ");
    int i = 0;

    while (i < length) {
        if (i == length - 1) {
            printf("%d", procArray[i]->pid);
        }

        else {
            printf("%d, ", procArray[i]->pid);
        }

        i++;
    }

    printf("]\n");
}


void fcfs(struct process** procArray, int length) {

    // all of these are in milliseconds
    char* firstLine = "Id, Arrival, Burst, Start, Finish, Wait, Turnaround, Response Time\n";
    char* standard =  "%2d, %7d, %5d, %5d, %6d, %4d, %10d, %13d\n";
    char* finalThree ="Average waiting time: %5.2f\nAverage turnaround time: %5.2f\nAverage response time: %5.2f\n";
    int i;

    // listing off a bunch of the vars to be printed    
    int id, arrival, burst, start, finish, wait, turnaround, respTime;
    // defining a bunch of the values to determine averages
    float totalWaitingTime, totalTurnTime, totalRespTime;

    // printing the initial sequence
    printSequence(procArray, length);
    printf("\n");

    // printing the first line of the table
    printf(firstLine);

    while (i < length) {

        id = procArray[i]->pid; arrival = procArray[i]->arrival; burst = procArray[i]->burstLength;
        start = arrival; finish = arrival + burst; wait = 0; turnaround = burst; respTime = 0;

        totalWaitingTime += wait; totalTurnTime += turnaround; totalRespTime += respTime;

        printf(standard, id, arrival, burst, start, finish, wait, turnaround, respTime);

        i++;
    }

    // converting these to the averages, ought to update the variable names
    totalWaitingTime /= length; totalTurnTime /= length; totalRespTime /= length;

    printf(finalThree, totalWaitingTime, totalTurnTime, totalRespTime);
}
