#ifndef MAIN_H
#define MAIN_H

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