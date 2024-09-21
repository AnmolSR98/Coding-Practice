#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define pos_int 2147483647
#include "main.h"

// just need to fix pop function, then spn is good to go

// code for a min heap of processes, sorted by burst length

struct process* createProcess(char* pid, char* arrival, char* time, char* burst) {

    struct process* newProcess = malloc(sizeof(struct process));

    newProcess->pid = atoi(pid);
    newProcess->arrival = atoi(arrival);
    newProcess->timeTilFirstResp = atoi(time);
    newProcess->burstLength = atoi(burst);

    return newProcess;
}

struct heap{
    struct process** someArray;
    int size;
    int length;
    int currentIndex;
};

bool isEmpty(struct heap* someHeap){
    if (someHeap->size == 0) {
        return true;
    }

    return false;
}

bool isFull(struct heap* someHeap) {
    if (someHeap->size == someHeap->length) {
        return true;
    }

    return false;
}

struct heap* createHeap(int length){
    
    struct heap* newHeap = (struct heap*) malloc( sizeof( struct heap ) );
    newHeap->size = 0;
    newHeap->currentIndex = 0;
    newHeap->length = length;
    newHeap->someArray = malloc( length * sizeof( struct process ) );

    return newHeap;

}

int getParent(int index){
    return ( (index - 1) / 2 );
}

int getRightChild(int index) {
    return ( index*2 + 2 );
}

int getLeftChild(int index) {
    return ( index*2 + 1 );
}

void swap(int a, int b, struct process** array){
    struct process* temp = array[a];
    array[a] = array[b];
    array[b] = temp;
}

int addProc(struct process* someProcess, struct heap* someHeap){

    struct process** array = someHeap->someArray;

    if (!isFull(someHeap)) {

        int i = someHeap->currentIndex;
        array[i] = someProcess;

        bool loop = true;

        while (loop) {

            if (array[i]->burstLength < array[getParent(i)]->burstLength) {
                swap(i, getParent(i), array);
                i = getParent(i);
            }

            else {
                loop = false;
            }

        }

        someHeap->size += 1;
        someHeap->currentIndex += 1;

        return 0;
    }

    else {
        return (-1);
    }

}

// bug is occuring here with regards to actually popping, may have to use place holder processes here
// something else is occuring now, some error when it gets close to the end values
// also error where it continues to sprinkle in values incorrectly
struct process* pop(struct heap* someHeap){

    if (isEmpty(someHeap)) {
        return 0;
    }    

    struct process** array = someHeap->someArray;
    struct process* returnValue = array[0];
    struct process* placeHolder = createProcess("0", "0", "0", "100000000");
    array[0] = placeHolder;
    int i = 0;

    while (i < someHeap->size) {

        if (getRightChild(i) < someHeap->size) {
            
            if (array[getLeftChild(i)]->burstLength < array[getRightChild(i)]->burstLength){
                swap(i, getLeftChild(i), array);
                i = getLeftChild(i);
            }

            else {
                swap(i, getRightChild(i), array);
                i = getRightChild(i);
            }

        }

        else if (getLeftChild(i) < someHeap->size) {

            swap(i, getLeftChild(i), array);
            i = getLeftChild(i);
        }

        else {

            if (i != someHeap->size - 1) {
                swap(i, someHeap->size - 1, array);
            }

            i = someHeap->size;
        }

    }

    someHeap->size -= 1;
    someHeap->currentIndex -= 1;

    return returnValue;
}