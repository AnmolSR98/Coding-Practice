#include <stdbool.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};

typedef struct {
    struct node* head;
} queue;

// returns false only if head is uninitialized
bool isEmpty(queue* someQueue) {
    
    if (someQueue->head != NULL){
        return true;
    }

    return false;
}

// 0 in this reading means false
bool isFull(queue* someQueue) {
    return false;
}

bool contains(queue* someQueue, int someNumber) {

    struct node* temp = someQueue->head;
    int returnData = temp->data;

    while (temp != NULL) {

        if (returnData == someNumber) {
            return true;
        }

        else {
            temp = temp->next;
        }
    }

    return false;
}

void remove(queue* someQueue, int someData) {

    if (!contains(someQueue, someData)) {
        return;
    }

    struct node* temp = someQueue->head;
    struct node* prev;
    int returnData = temp->data;
}


// if it is not empty, cycle to the next 
void enqueue(queue* someQueue, int someData){
    
    if (isEmpty(someQueue)){
        return;
    }    

    struct node* temp = someQueue->head;

    while (temp->next != NULL){
        temp = temp->next;
    }

    struct node *newNode = (struct node*) malloc(sizeof(struct node));
    newNode->data = someData;
    if (isEmpty(someQueue)){
        return;
    }    

    temp->next = newNode;
}

// dequeue provided that the queue is not empty, cycle the head forward
int dequeue(queue* someQueue, int data) {

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