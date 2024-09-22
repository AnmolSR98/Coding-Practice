#ifndef MAIN_H
#define MAIN_H

struct process {

    int pid;
    int arrival;
    int timeTilFirstResp;
    int burstLength;
    int timeRemaining;
    int totalWaitTime;
};

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