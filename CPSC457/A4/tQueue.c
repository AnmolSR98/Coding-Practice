#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// creating a node that contains an id and the next variable in the chain
struct node {
    pthread_t* id;
    pthread_cond_t* cond;
    struct node* next;
};

// the actual queue itself
typedef struct {
    volatile int size;
    struct node* head;
    struct node* holder;
} threadQueue;

// the queue initialization method
threadQueue* createQueue() {

    threadQueue* newQueue = (threadQueue*) malloc( sizeof(threadQueue*) );
    newQueue->size = 0;
    return newQueue;
}

// method for adding a thread to the queue
void enqueue(threadQueue* someQueue, pthread_t* someThread, pthread_cond_t* someCond) {

    // creating the node and filling out the necessary details for it
    struct node* newNode = (struct node*) malloc( sizeof(struct node*) );
    newNode->id = someThread;
    newNode->cond = someCond;

    // if the threadQueue is empty, just insert it in as the head
    if (someQueue->size == 0) {
        someQueue->head = newNode;
    }

    // otherwise cycle through to the end and insert it there
    else {
        someQueue->holder = someQueue->head;
        int j;
        for (j = 0; j < someQueue->size-1; j++) {
            someQueue->holder = someQueue->holder->next;
        }
        

        someQueue->holder->next = newNode;
    }

    // increment the size
    someQueue->size++;
}

// method to remove something from the queue
struct node* dequeue(threadQueue* someQueue) {

    struct node* nodeToRemove;

    // just return null, don't trigger an exception
    if (someQueue->size == 0) {
        return NULL;
    }

    // cycle the head forward and decrement the size
    else {
        nodeToRemove = someQueue->head;
        someQueue->size--;
        if (someQueue->head != NULL) {someQueue->head = someQueue->head->next;}
        return nodeToRemove;
    }
}
