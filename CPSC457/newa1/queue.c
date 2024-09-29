#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "main.h"

// linked list based implementation of a queue
struct node {
    struct process* storedProcess;
    struct node* next;
};

struct queue {
    struct node* head;
    int size;
};

struct queue* createQueue() {

    struct queue* newQueue = (struct queue*) malloc(sizeof(struct queue));
    newQueue->head = NULL;
    newQueue->size = 0;

}

// returns false only if head is uninitialized
bool isEmpty(struct queue* someQueue) {
    
    if (someQueue->head == NULL){
        return true;
    }

    return false;
}

// 0 in this reading means false
bool isFull(struct queue* someQueue) {
    return false;
}

// if it is not empty, cycle to the next 
void enqueue(struct queue* someQueue, struct process* someProcess){
    
    struct node* temp = someQueue->head;
    someQueue->size += 1;

    struct node *newNode = (struct node*) malloc(sizeof(struct node));
    newNode->storedProcess = someProcess;
    newNode->next = NULL;

    if (isEmpty(someQueue)){
        someQueue->head = newNode;
        return;
    }    

    else {

        while (temp->next != NULL){
            temp = temp->next;
        }

        temp->next = newNode;
    }
}

// dequeue provided that the queue is not empty, cycle the head forward
struct process* dequeue(struct queue* someQueue) {

    if (isEmpty(someQueue)){
        return NULL;
    }    

    someQueue->size -= 1;
    struct node* temp = someQueue->head;
    struct process* returnData = temp->storedProcess;
    someQueue->head = someQueue->head->next;
    free(temp);
    return returnData;
}


