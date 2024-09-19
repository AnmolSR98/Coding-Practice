#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define buffer 64
#define numAttr 4
#define expectedLength 16
#define pid_column 0
#define arr_column 1
#define tim_column 2
#define bur_column 3

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



int main() {

    // most crucial thing right now is to get the number of lines in an input file

    // https://stackoverflow.com/questions/12911299/read-csv-file-in-c
    // perhaps change to another name otherwise it may not work properly when TA has to run[]
    FILE* inputCSV = fopen("input.csv", "r");

    struct process** processesArray[1001];

    // ie an array to temporarily hold each string before it is converted to an 
    char inputString[buffer];
    char inputString2[buffer];
    // array to hold 4 strings
    char* cycler;
    char holderArray[numAttr][expectedLength]; 
    // an array to run for as many lines are in the input file
    int i = 0;
    // fgets seems to divy it up by \n anyways, run a for loop here
    while (i < 1001) {
        
        fgets(inputString, buffer, inputCSV);
        // need to use strtok 
        cycler = strtok(inputString, ",");
        //use this to cycle it through
        strcpy(holderArray[pid_column], cycler);
        strcpy(holderArray[arr_column], strtok(NULL, ","));
        strcpy(holderArray[tim_column], strtok(NULL, ","));
        strcpy(holderArray[bur_column], strtok(NULL, ","));

        processArray[i] = createProcess(holderArray[pid_column], holderArray[arr_column], holderArray[tim_column], holderArray[bur_column]);

        printf("%s\n", holderArray[pid_column]);
        i++;
    }


    fclose(inputCSV);
    // end of snippet from above site

    return 0;
}