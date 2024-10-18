#include <stdbool.h>
#include <stdlib.h>

// struct node
struct node {
    int data;
    struct node* next;
};

// ll queue that contains head
typedef struct {
    struct node* head;
} queue;

// creation method, just allocates memory, nothing else
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

// always returns false
bool isFull(queue* someQueue) {
    return false;
}

// function to see if a number is already in the queue
bool contains(queue* someQueue, int someNumber) {

    if (isEmpty(someQueue)) {
        return false;
    }

    struct node* temp = someQueue->head;

    // just cycle through to see if it is in the queue
    while (temp != NULL) {

        if (temp->data == someNumber) {
            return true;
        }

        else {
            temp = temp->next;
        }
    }

    // otherwise return false
    return false;
}

// function to remove an element from a queue, not dequeue (ie. can remove regardless of where it is in queue)
int removeFromQueue(queue* someQueue, int someData) {

    // verify that the queue is not empty and verify that the element is in queue
    if (isEmpty(someQueue)) {
        return (-1);
    }

    if (!contains(someQueue, someData)) {
        return (-1);
    }

    // create some nodes, prev will store the prior value of temp
    struct node* temp = someQueue->head;
    struct node* prev;
    bool loop = true;

    while (loop) {
        
        // if the value is found
        if (temp->data == someData) {

            // if it is the head, just shuffle the head forward
            if (temp == someQueue->head) {
                someQueue->head = someQueue->head->next;
            }

            // otherwise, break the queue around it, linking the prior node to the next node
            else {
                prev->next = temp->next;
            }
        
            // free the node and kill the loop
            free(temp);
            loop = false;
        }

        else {
            // otherwise cycle loop
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL) {
            // kill the loop if temp is null
            loop = false;
        }

    }

    return 0;
}


// if it is not empty, cycle to the end to place the new node there
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

// dequeue provided that the queue is not empty, simply cycle the head forward
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
