#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define pos_int 2147483647
#include <time.h>

// writing code for a min heap
// gonna need a fix for what to do for NULLs [DONE]

struct heap{
    int* someArray;
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
    newHeap->someArray = malloc( length * sizeof(int) );

    int i;
    for (i = 0; i < length; i++) {
        newHeap->someArray[i] = pos_int;
    }

    return newHeap;

}

int getParent(int index){
    return ( index / 2 );
}

int getRightChild(int index) {
    return ( index*2 + 2 );
}

int getLeftChild(int index) {
    return ( index*2 + 1 );
}

void swap(int a, int b, int* array){
    int temp = array[a];
    array[a] = array[b];
    array[b] = temp;
}

int addValue(int value, struct heap* someHeap){

    int* array = someHeap->someArray;

    if (!isFull(someHeap)) {

        int i = someHeap->currentIndex;
        array[i] = value;

        bool loop = true;

        while (loop) {

            if (array[i] < array[getParent(i)]) {
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

int pop(struct heap* someHeap){

    if (isEmpty(someHeap)) {
        return 0;
    }

    int* array = someHeap->someArray;
    int returnValue = array[0];
    array[0] = pos_int;
    int i = 0;

    while (i < someHeap->size) {

        if (getRightChild(i) < someHeap->length) {
            
            if (array[getLeftChild(i)] < array[getRightChild(i)]){
                swap(i, getLeftChild(i), array);
                i = getLeftChild(i);
            }

            else {
                swap(i, getRightChild(i), array);
                i = getRightChild(i);
            }

        }

        else if (getLeftChild(i) < someHeap->length) {

            swap(i, getLeftChild(i), array);
            i = getLeftChild(i);
        }

        else {
            i = someHeap->size;
        }

    }

    someHeap->size -= 1;
    someHeap->currentIndex -= 1;

    return returnValue;
}



