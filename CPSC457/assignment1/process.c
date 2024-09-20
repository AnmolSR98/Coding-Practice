#include <stdlib.h>
#include <stdio.h>

struct process {

    int pid;
    int arrival;
    int timeTilFirstResp;
    int burstLength;
};

// function that creates a new process based on string inputs
struct process* createProcess(char* pid, char* arrival, char* time, char* burst) {

    struct process* newProcess = malloc(sizeof(struct process));

    newProcess->pid = atoi(pid);
    newProcess->arrival = atoi(arrival);
    newProcess->timeTilFirstResp = atoi(time);
    newProcess->burstLength = atoi(burst);

    return newProcess;
}