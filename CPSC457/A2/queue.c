#include <stdbool.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};

typedef struct {
    struct node* head;
} queue;

queue* createQueue() {

    queue* newQueue = (queue*) malloc(sizeof(queue));
    newQueue->head = NULL;
}

// returns false only if head is uninitialized
bool isEmpty(queue* someQueue) {
    
    if (someQueue->head == NULL){
        return true;
    }

    return false;
}

bool isFull(queue* someQueue) {
    return false;
}

// function to see if a number is already in the queue
bool contains(queue* someQueue, int someNumber) {

    if (isEmpty(someQueue)) {
        return false;
    }

    struct node* temp = someQueue->head;

    while (temp != NULL) {

        if (temp->data == someNumber) {
            return true;
        }

        else {
            temp = temp->next;
        }
    }

    return false;
}

// function to remove an element from a queue
int removeFromQueue(queue* someQueue, int someData) {

    if (!contains(someQueue, someData)) {
        return (-1);
    }

    if (isEmpty(someQueue)) {
        return (-1);
    }

    struct node* temp = someQueue->head;
    struct node* prev;
    bool loop = true;

    while (loop) {
        
        if (temp->data == someData) {

            if (temp == someQueue->head) {
                someQueue->head = someQueue->head->next;
            }

            else {
                prev->next = temp->next;
            }
        
            free(temp);
            loop = false;
        }

        else {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL) {
            loop = false;
        }

    }

    return 0;
}


// if it is not empty, cycle to the next 
void enqueue(queue* someQueue, int someData){
    
    struct node* temp = someQueue->head;

    struct node *newNode = (struct node*) malloc(sizeof(struct node));
    newNode->data = someData;
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
int dequeue(queue* someQueue) {

    if (isEmpty(someQueue)){
        return (-1);
    }    

    struct node* temp = someQueue->head;
    int returnData = temp->data;
    someQueue->head = someQueue->head->next;
    free(temp);
    return returnData;
}

/**
int main() {

    queue* someQueue = createQueue();
    enqueue(someQueue, 30);
    enqueue(someQueue, 294);
    removeFromQueue(someQueue, 294);

    return 0;
}*/