#include <stdio.h>
#include <stdlib.h>

// need to free up nodes that get deleted ie. deallocate memory [X]

struct node {
    int data;
    struct node* next;
};

struct queue {
    struct node* head;
};

// returns false only if head is uninitialized
int isEmpty(struct queue* someQueue) {
    
    if (someQueue->head != NULL){
        return 1;
    }

    return 0;
}

// 0 in this reading means false
int isFull(struct queue* someQueue) {
    return 0;
}

// if it is not empty, cycle to the next 
void enqueue(struct queue* someQueue, int someData){
    
    if (isEmpty(someQueue)){
        return;
    }    

    struct node* temp = someQueue->head;

    while (temp->next != NULL){
        temp = temp->next;
    }

    struct node *newNode = (struct node*) malloc(sizeof(struct node));
    newNode->data = someData;if (isEmpty(someQueue)){
        return;
    }    

    temp->next = newNode;
}

// dequeue provided that the queue is not empty, cycle the head forward
int dequeue(struct queue* someQueue, int data) {

    if (isEmpty(someQueue)){
        return (-1);
    }    

    struct node* temp = someQueue->head;
    int returnData = temp->data;
    someQueue->head = someQueue->head->next;
    free(temp);
    return returnData;
}



int main() {
    return 0;
}