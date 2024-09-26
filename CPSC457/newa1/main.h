#ifndef MAIN_H
#define MAIN_H

#include "queue.c"

// all of these are in milliseconds
char* firstLine = 
"+----+---------+-------+-------+--------+-------+-------------+---------------+\n| Id | Arrival | Burst | Start | Finish | Wait  | Turnaround  | Response Time |\n+----+---------+-------+-------+--------+-------+-------------+---------------+\n";
char* standard =  "| %2d | %7d | %5d | %5d | %6d | %5d | %11d | %13d |\n";
char* tableCloser = "+----+---------+-------+-------+--------+-------+-------------+---------------+\n";
char* finalThree ="Average waiting time: %5.2f\nAverage turnaround time: %5.2f\nAverage response time: %5.2f\n";

struct process {

    int pid;
    int arrival;
    int timeTilFirstResp;
    int burstLength;
    int timeRemaining;
    int prevEndTime;
    bool hasResponded;
};

struct totalProcess {

    int pid;
    int arrive;
    int burst;
    int start;
    int finish;
    int wait;
    int turnaround;
    int response;

};

void copyArray(struct process** original, struct process** duplicate, int length) {

    int i;
    for (i = 0; i < length; i++) {
        duplicate[i] = original[i];
    }
}

int getIndexOfLastArrivedProcess(struct process** procArray, int time, int arrayLength) {

    int i = 0;
    while (procArray[i]->arrival < time) {
        if (i == arrayLength - 1) {
            return arrayLength - 1;
        }
        i++;
    }

    return i;
}

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

    return newTotalProcess;
}

struct process* createProcess(char* pid, char* arrival, char* time, char* burst) {

    struct process* newProcess = malloc(sizeof(struct process));

    newProcess->pid = atoi(pid);
    newProcess->arrival = atoi(arrival);
    newProcess->timeTilFirstResp = atoi(time);
    newProcess->burstLength = atoi(burst);
    newProcess->timeRemaining = newProcess->burstLength;
    newProcess->hasResponded = false;

    return newProcess;
}

void swap(int a, int b, struct process** array){

    struct process* temp = array[a];
    array[a] = array[b];
    array[b] = temp;
}

void updateTotal(struct totalProcess* someTotal, int arrive, int burst, int start, int finish, int response) {


    if (someTotal->arrive == -1) {
        someTotal->arrive = arrive;
    }
    
    if (someTotal->start == -1) {
        someTotal->start = start;
    }

    someTotal->burst += burst;

    someTotal->finish = finish;

    someTotal->wait = start - arrive;

    someTotal->turnaround = finish - arrive;

    if (someTotal->response == -1) {
        someTotal->response = response - arrive;
    }

}

// going to have to get implement this into the while loop for each of the individual files, as it is executing and calculating
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

#endif