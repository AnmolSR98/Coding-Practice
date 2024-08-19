#include <stdio.h>
#include <stdlib.h>

// need to free up nodes that get released ie. deallocate memory []

struct node {
    int data;
    struct node* next;
};

struct stack{
    struct node* head;
};

int isEmpty(struct stack* someStack){
    if (someStack->head == NULL){
        return 1;
    }

    return 0;
}

int isFull(struct stack* someStack) {
    return 0;
}

void push(struct stack* someStack, int someData){
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = someData;
    newNode->next = someStack->head;
    someStack->head = (struct node*) newNode;
}

int pop(struct stack* someStack){
    if (isEmpty(someStack)){
        struct node* temp = someStack->head;
        int returnData = temp->data;
        someStack->head = someStack->head->next;
        free(temp);
        return returnData;
    }

    return NULL;
}

int peek(struct stack* someStack){
    if (isEmpty(someStack)){
        return someStack->head->data;
    }

    return NULL;
}


int main(){
    return 0;
}