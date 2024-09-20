#ifndef MAIN_H
#define MAIN_H

struct process {

    int pid;
    int arrival;
    int timeTilFirstResp;
    int burstLength;
};

void printSequence(struct process** procArray, int length) {

    printf("seq = [ ");
    int i = 0;

    while (i < length) {
        if (i == length - 1) {
            printf("%d: %d", i, procArray[i]->burstLength);
        }

        else {
            printf("%d: %d, ",i, procArray[i]->burstLength);
        }

        i++;
    }

    printf("]\n");
}

#endif