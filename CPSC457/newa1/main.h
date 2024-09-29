#ifndef MAIN_H
#define MAIN_H

// including queue.c for use in functions later in main.h
#include "queue.c"

// strings to be used for the print statements all of these are in milliseconds
char* firstLine = 
"+----+---------+-------+-------+--------+-------+-------------+---------------+\n| Id | Arrival | Burst | Start | Finish | Wait  | Turnaround  | Response Time |\n+----+---------+-------+-------+--------+-------+-------------+---------------+\n";
char* standard =  "| %2d | %7d | %5d | %5d | %6d | %5d | %11d | %13d |\n";
char* tableCloser = "+----+---------+-------+-------+--------+-------+-------------+---------------+\n";
char* finalThree ="Average waiting time: %5.2f ms\nAverage turnaround time: %5.2f ms\nAverage response time: %5.2f ms\n";

// struct definitions for each individual thread
struct process {

    int pid;
    int arrival;
    int timeTilFirstResp;
    int burstLength;
    int timeRemaining;
    bool hasResponded;
    // for RR calculations
    int prevEndTime;
};

// struct definition for total of each process
struct totalProcess {

    int pid;
    int arrive;
    int burst;
    int start;
    int finish;
    int wait;
    int turnaround;
    int response;
    double prevBurst;
    double actualRemainingTime;
    double estimatedRemainingTime;
    double exponentialAverage;

};

// getting the index of the last process to arrive
int getIndexOfLastArrivedProcess(struct process** procArray, int time, int arrayLength) {

    int i = 0;
    while (procArray[i]->arrival <= time) {
        if (i == arrayLength - 1) {
            return arrayLength - 1;
        }
        i++;
    }

    return i - 1;
}

// total process creation method
struct totalProcess* createTotalProcess(int pid) {

    struct totalProcess* newTotalProcess = malloc(sizeof(struct totalProcess));

    newTotalProcess->pid = pid;
    newTotalProcess->arrive = -1;
    newTotalProcess->burst = 0;
    newTotalProcess->start = -1;
    newTotalProcess->finish = 0;
    newTotalProcess->wait = 0;
    newTotalProcess->turnaround = 0;
    newTotalProcess->response = -1;
    newTotalProcess->estimatedRemainingTime = -1;
    newTotalProcess->prevBurst = -1;

    return newTotalProcess;
}

// process creation method, for strings
struct process* createProcess(char* pid, char* arrival, char* time, char* burst) {

    struct process* newProcess = malloc(sizeof(struct process));

    newProcess->pid = atoi(pid);
    newProcess->arrival = atoi(arrival);
    newProcess->timeTilFirstResp = atoi(time);
    newProcess->burstLength = atoi(burst);
    newProcess->timeRemaining = newProcess->burstLength;
    newProcess->hasResponded = false;
    newProcess->prevEndTime = -1;

    return newProcess;
}

// process creation method, for integers
struct process* createProcessAlt(int pid, int arrival, int time, int burst) {

    struct process* newProcess = malloc(sizeof(struct process));

    newProcess->pid = pid;
    newProcess->arrival = arrival;
    newProcess->timeTilFirstResp = time;
    newProcess->burstLength = burst;
    newProcess->timeRemaining = newProcess->burstLength;
    newProcess->hasResponded = false;
    newProcess->prevEndTime = -1;

    return newProcess;

}

// method to copy arrays
void copyArray(struct process** original, struct process** duplicate, int length) {

    struct process* currentProc = malloc(sizeof(struct process));
    int i;
    for (i = 0; i < length; i++) {
        currentProc = original[i];
        duplicate[i] = createProcessAlt(currentProc->pid, currentProc->arrival, currentProc->timeTilFirstResp, currentProc->burstLength);
    }

    free(currentProc);
}

// method to swap two processes in the process array
void swap(int a, int b, struct process** array){

    struct process* temp = array[a];
    array[a] = array[b];
    array[b] = temp;
}

// method to update the information on a process, used after a thread is either rotated out or if it finished executing
void updateTotal(struct totalProcess* someTotal, int arrive, int burst, int start, int finish, int response) {


    if (someTotal->arrive == -1) {
        someTotal->arrive = arrive;
    }
    
    if (someTotal->start == -1) {
        someTotal->start = start;
    }

    someTotal->burst += burst;

    someTotal->finish = finish;

    someTotal->wait += (start - arrive);

    someTotal->turnaround = finish - arrive;

    if (someTotal->response == -1) {
        someTotal->response = response - arrive;
    }

}

// print function to be used after all processes have been completed
double* printTable(struct totalProcess** totalsArray, int length) {

    printf(firstLine);
    double totalWaitingTime, totalTurnTime, totalRespTime;
    struct totalProcess* currentTotal = (struct totalProcess*) malloc(sizeof(struct totalProcess));
    int i;
    for (i = 0; i < length; i++) {
        // printing off a new column
        currentTotal = totalsArray[i];
        // updating the totals
        totalWaitingTime += currentTotal->wait; totalTurnTime += currentTotal->turnaround; totalRespTime += currentTotal->response;
        printf(standard, currentTotal->pid, currentTotal->arrive, currentTotal->burst, currentTotal->start, currentTotal->finish, currentTotal->wait, currentTotal->turnaround, currentTotal->response);
    }
    printf(tableCloser);

    // converting these to the averages, ought to update the variable names
    totalWaitingTime /= length; totalTurnTime /= length; totalRespTime /= length;

    printf(finalThree, totalWaitingTime, totalTurnTime, totalRespTime);

    double* averageArray = malloc(sizeof(double) * 3);
    averageArray[0] = totalWaitingTime;
    averageArray[1] = totalTurnTime;
    averageArray[2] = totalRespTime;

    return averageArray;
}

// simple maximum function here
int maximum(int a, int b) {
    if (a >= b) {
        return a;
    }

    return b;
}

#endif