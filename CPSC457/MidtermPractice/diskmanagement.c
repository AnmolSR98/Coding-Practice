#include <stdlib.h>
#include <stdio.h>
#include "queue.c"

#define min 0
#define max 199

// simple first come first serve algorithm
int FCFS(queue* requests, int length) {

    int head = dequeue(requests);
    int totalCylinders = 0;
    int current = head;
    int next;

    while (!isEmpty(requests)) {
        next = dequeue(requests);
        totalCylinders += abs(current - next);
        current = next;
    }

    return totalCylinders;
}

// helper function to get the one with the least distance
int getLowestDifferenceInQueue(queue* someQueue, int n, int length) {

    int lowest = 200000;
    int current = 0;
    int i;
    for (i = 0; i < length; i++) {
        current = dequeue(someQueue);
        if (abs(n - current) < abs(n - lowest) ) {
            if (lowest != 200000) {
                enqueue(someQueue, lowest);
            }
            lowest = current;
        }

        else {
            enqueue(someQueue, current);
        }
    }

    return lowest;

}

// shortest seek time first algorithm
int SSTF(queue* requests, int length) {

    int head = dequeue(requests);
    int totalCylinders = 0;
    int current = head;
    int next = 0;
    length--;

    while (!isEmpty(requests)) {
        next = getLowestDifferenceInQueue(requests, current, length);
        totalCylinders += abs(current - next);
        current = next;
        length--;
    }

    return totalCylinders;

}

// 

int howManyLargerThan(queue* someQueue, int n, int length) {

    int howmany = 0;
    int current = 0;

    int i;
    for (i = 0; i < length; i++) {
        current = dequeue(someQueue);
        
        if (current > n) {
            howmany++;
        }

        enqueue(someQueue, current);
    }

    return howmany;

}

// SCAN algorithm 
int SCAN(queue* requests, int length) {

    int head = dequeue(requests);
    int totalCylinders = 0;
    int current = 0;
    int next = 0;
    length--;

    queue* lowerQueue = createQueue();

    int lowerLength = length - howManyLargerThan(requests, head, length);

    int i;
    for (i = 0; i < length; i++) {
        current = dequeue(requests);
        if (current < head) {
            enqueue(lowerQueue, current);
            length--;
        }

        else {
            enqueue(requests, current);
        }
    }

    current = head;

    while (!isEmpty(lowerQueue)) {
        next = getLowestDifferenceInQueue(lowerQueue, current, lowerLength);
        totalCylinders += abs(current - next);
        current = next;
        lowerLength--;
    }

    totalCylinders += abs(current - min);
    current = min;

    while (!isEmpty(requests)) {
        next = getLowestDifferenceInQueue(requests, current, length);
        totalCylinders += abs(current - next);
        current = next;
        length--;
    }

    return totalCylinders;
}

// SCAN algorithm 
int CSCAN(queue* requests, int length) {

    int head = dequeue(requests);
    int totalCylinders = 0;
    int current = 0;
    int next = 0;
    length--;

    queue* lowerQueue = createQueue();

    int lowerLength = length - howManyLargerThan(requests, head, length);

    int i;
    for (i = 0; i < length; i++) {
        current = dequeue(requests);
        if (current < head) {
            enqueue(lowerQueue, current);
            length--;
        }

        else {
            enqueue(requests, current);
        }
    }

    current = head;

    while (!isEmpty(requests)) {
        next = getLowestDifferenceInQueue(requests, current, length);
        totalCylinders += abs(current - next);
        current = next;
        length--;
    }

    next = max;
    totalCylinders += abs(current - next);
    current = next;

    next = min;
    totalCylinders += abs(current - next);
    current = next;

    while (!isEmpty(lowerQueue)) {
        next = getLowestDifferenceInQueue(lowerQueue, current, lowerLength);
        totalCylinders += abs(current - next);
        current = next;
        lowerLength--;
    }

    return totalCylinders;
}

int CLOOK(queue* requests, int length) {
    
    int head = dequeue(requests);
    int totalCylinders = 0;
    int current = 0;
    int next = 0;
    length--;
    int minimum = getLowestDifferenceInQueue(requests, 0, length);
    length--;

    queue* lowerQueue = createQueue();

    int lowerLength = length - howManyLargerThan(requests, head, length);

    int i;
    for (i = 0; i < length; i++) {
        current = dequeue(requests);
        if (current < head) {
            enqueue(lowerQueue, current);
            length--;
        }

        else {
            enqueue(requests, current);
        }
    }

    current = head;

    while (!isEmpty(requests)) {
        next = getLowestDifferenceInQueue(requests, current, length);
        totalCylinders += abs(current - next);
        current = next;
        length--;
    }

    next = minimum;
    totalCylinders += abs(current - next);
    current = next;

    while (!isEmpty(lowerQueue)) {
        next = getLowestDifferenceInQueue(lowerQueue, current, lowerLength);
        totalCylinders += abs(current - next);
        current = next;
        lowerLength--;
    }

    return totalCylinders;
}

int main(){

    queue* testQueue = createQueue();

    enqueue(testQueue, 53); enqueue(testQueue, 98); enqueue(testQueue, 183); enqueue(testQueue, 37);
    enqueue(testQueue, 122); enqueue(testQueue, 14); enqueue(testQueue, 124); enqueue(testQueue, 65); enqueue(testQueue, 67); 

    int length = 9;
    int cyl = CLOOK(testQueue, length);

    return 0;
}

