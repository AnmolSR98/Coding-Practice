#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "main.h"
#include "queue.c"
#define buffer 64
#define numAttr 4
#define expectedLength 16
#define pid_column 0
#define arr_column 1
#define tim_column 2
#define bur_column 3


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

struct process* createProcess(char* pid, char* arrival, char* time, char* burst) {

    struct process* newProcess = malloc(sizeof(struct process));

    newProcess->pid = atoi(pid);
    newProcess->arrival = atoi(arrival);
    newProcess->timeTilFirstResp = atoi(time);
    newProcess->burstLength = atoi(burst);

    return newProcess;
}

void swap(int a, int b, struct process** array){

    struct process* temp = array[a];
    array[a] = array[b];
    array[b] = temp;
}

void insertionSort(struct process** procArray, int length) {

    int i = 1, j;
    while (i < length) {
        j = i;
        while ((j > 0) && (procArray[j - 1]->pid > procArray[j]->pid) && (procArray[j - 1]->arrival == procArray[j]->arrival)) {
            swap(j, j - 1, procArray);
            j--;
        }
        i++;
    }
}

void fcfs(struct process** procArray, int length) {

    // all of these are in milliseconds
    char* firstLine = "  Id, Arrival, Burst, Start, Finish, Wait, Turnaround, Response Time\n";
    char* standard =  "%4d, %7d, %5d, %5d, %6d, %4d, %10d, %13d\n";
    char* finalThree ="\nAverage waiting time: %5.2f ms\nAverage turnaround time: %5.2f ms\nAverage response time: %5.2f ms\n";
    int i;

    // listing off a bunch of the vars to be printed    
    int id, arrival, burst, start, finish, wait, turnaround, respTime;
    // defining a bunch of the values to determine averages
    float totalWaitingTime, totalTurnTime, totalRespTime;

    // feeding the input array into a queue
    struct queue* procQueue = createQueue();
    for (i = 0; i < length; i++) {
        enqueue(procQueue, procArray[i]);
    }

    int numUniqueProcs = 50;

    struct totalProcess* totalsArray[50];
    for (i = 0; i < numUniqueProcs; i++) {
        totalsArray[i] = createTotalProcess(i+1);
    }

    // printing the initial sequence
    printSequence(procArray, length);
    printf("\n");

    // printing the first line of the table
    printf(firstLine);

    struct process* currentProc;
    int currentTime = procArray[0]->arrival;

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
    }

    struct totalProcess* currentTotal = (struct totalProcess*) malloc(sizeof(struct totalProcess));
    for (i = 0; i < numUniqueProcs; i++) {
        // printing off a new column
        currentTotal = totalsArray[i];
        // updating the totals
        totalWaitingTime += currentTotal->wait; totalTurnTime += currentTotal->turnaround; totalRespTime += currentTotal->response;
        printf(standard, currentTotal->pid, currentTotal->arrive, currentTotal->burst, currentTotal->start, currentTotal->finish, currentTotal->wait, currentTotal->turnaround, currentTotal->response);
    }

    // converting these to the averages, ought to update the variable names
    totalWaitingTime /= numUniqueProcs; totalTurnTime /= numUniqueProcs; totalRespTime /= numUniqueProcs;

    printf(finalThree, totalWaitingTime, totalTurnTime, totalRespTime);
}

int main() {

    // most crucial thing right now is to get the number of lines in an input file
    // PROCESSES ARE BEING READ IN CORRECTLY 
    // maybe use feof to determine end of file

    // https://stackoverflow.com/questions/12911299/read-csv-file-in-c
    // perhaps change to another name otherwise it may not work properly when TA has to run[]
    
    // actual input file
    FILE* inputCSV = fopen("input.csv", "r");
    // array of pointers to processes
    struct process* processArray[1000];
    // ie an array to temporarily hold each string before it is converted to an 
    char inputString[buffer];
    // array to hold the strings from cycler, which are then passed on the createProcess
    char holderArray[numAttr][expectedLength]; 
    // an array to run for as many lines are in the input file
    int i = 0;
    // fgets seems to divy it up by \n anyways, run a for loop here
    while (i < 1001) {
        
        // reads in lines from csv line by line
        fgets(inputString, buffer, inputCSV);
        // using strtok to cycle through the various process attributes
        strcpy(holderArray[pid_column], strtok(inputString, ","));
        strcpy(holderArray[arr_column], strtok(NULL, ","));
        strcpy(holderArray[tim_column], strtok(NULL, ","));
        strcpy(holderArray[bur_column], strtok(NULL, ","));

        // adds them provided we are past the first line, so the text won't be added as an entry
        if (i > 0) {
            processArray[i - 1] = createProcess(holderArray[pid_column], holderArray[arr_column], holderArray[tim_column], holderArray[bur_column]);
        }

        // continue on through the lines
        i++;
    }

    // closing the input csv
    fclose(inputCSV);

    // working well enough
    fcfs(processArray, 1000);


    return 0;
}

