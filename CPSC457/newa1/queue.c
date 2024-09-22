#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "main.h"

// need to free up nodes that get deleted ie. deallocate memory [X]

struct node {
    struct process* process;
    struct node* next;
};

struct queue {
    struct node* head;
};

// returns false only if head is uninitialized
bool isEmpty(struct queue* someQueue) {
    
    if (someQueue->head != NULL){
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
    
    if (isEmpty(someQueue)){
        return;
    }    

    struct node* temp = someQueue->head;

    while (temp->next != NULL){
        temp = temp->next;
    }

    struct node *newNode = (struct node*) malloc(sizeof(struct node));
    newNode->process = someProcess;
    
    if (isEmpty(someQueue)){
        return;
    }    

    temp->next = newNode;
}

// dequeue provided that the queue is not empty, cycle the head forward
struct process* dequeue(struct queue* someQueue, int data) {

    if (isEmpty(someQueue)){
        return NULL;
    }    

    struct node* temp = someQueue->head;
    struct process* returnData = temp->process;
    someQueue->head = someQueue->head->next;
    free(temp);
    return returnData;
}


