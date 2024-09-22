#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "main.h"
#define buffer 64
#define numAttr 4
#define expectedLength 16
#define pid_column 0
#define arr_column 1
#define tim_column 2
#define bur_column 3


// going to have to use a insertion sort first

struct process* createProcess(char* pid, char* arrival, char* time, char* burst) {

    struct process* newProcess = malloc(sizeof(struct process));

    newProcess->pid = atoi(pid);
    newProcess->arrival = atoi(arrival);
    newProcess->timeTilFirstResp = atoi(time);
    newProcess->burstLength = atoi(burst);

    return newProcess;
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

void copyArray(struct process** original, struct process** duplicate, int length) {

    int i;
    for (i = 0; i < length; i++) {
        duplicate[i] = original[i];
    }
}

void swap(int a, int b, struct process** array){

    struct process* temp = array[a];
    array[a] = array[b];
    array[b] = temp;
}

void insertionSort(struct process** procArray, int lower, int upper) {

    int i = lower + 1, j;
    while (i < upper + 1) {
        j = i;
        while ((j > lower) && (procArray[j - 1]->burstLength > procArray[j]->burstLength)) {
            swap(j, j - 1, procArray);
            j--;
        }
        i++;
    }
}

void spn(struct process** procArray, int length) {

    // all of these are in milliseconds
    char* firstLine = "   Id, Arrival, Burst, Start, Finish, Wait, Turnaround, Response Time\n";
    char* standard =  "%2d, %7d, %5d, %5d, %6d, %4d, %10d, %13d\n";
    char* finalThree ="\nAverage waiting time: %5.2f ms\nAverage turnaround time: %5.2f ms\nAverage response time: %5.2f ms\n";
    int i;

    // listing off a bunch of the vars to be printed    
    int id, arrival, burst, start, finish, wait, turnaround, respTime;
    // defining a bunch of the values to determine averages
    double totalWaitingTime, totalTurnTime, totalRespTime;

    struct process* duplicateArray[1000];
    
    copyArray(procArray, duplicateArray, 1000);

    i = 0;

    // printing the initial sequence
    printSequence(procArray, length);
    printf("\n");

    // printing the first line of the table
    printf(firstLine);

    int currentTime = 0;
    i = 0;
    int max = 0;

    while (i < length) {

        max = 0;

        id = procArray[i]->pid; arrival = procArray[i]->arrival; burst = procArray[i]->burstLength;
        start = currentTime; finish = start + burst; wait = start - arrival; turnaround = burst; respTime = start + procArray[i]->timeTilFirstResp;

        i++;

        currentTime += burst;
        
        if (max < length) {
            max = getIndexOfLastArrivedProcess(duplicateArray, currentTime, length);
        }

        insertionSort(procArray, i, max);

        totalWaitingTime += currentTime; totalTurnTime += turnaround; totalRespTime += respTime;

        printf("%3d: ", i);
        printf(standard, id, arrival, burst, start, finish, wait, turnaround, respTime);

    }

    // converting these to the averages, ought to update the variable names
    totalWaitingTime /= length; totalTurnTime /= length; totalRespTime /= length;

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
    //fcfs(processArray, 1000);

    spn(processArray, 1000);

    return 0;
}