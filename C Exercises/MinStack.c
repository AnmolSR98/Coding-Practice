#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// need to free up nodes that get released ie. deallocate memory [DONE]

struct node {
    int data;
    struct node* next;
};

struct minStack{
    struct node* head;
};

bool isEmpty(struct minStack* someStack){
    if (someStack->head == NULL){
        return true;
    }

    return false;
}

bool isFull(struct minStack* someStack) {
    return false;
}

int pop(struct minStack* someStack){
    
    if (!isEmpty(someStack)){
        struct node* temp = someStack->head;
        int returnData = temp->data;
        someStack->head = someStack->head->next;
        free(temp);
        return returnData;
    }

    return (-1);
}

int peek(struct minStack* someStack){
    
    if (!isEmpty(someStack)){
        return someStack->head->data;
    }

    return (-1);
}

int push(struct minStack* someStack, int someData){
    
    if (isEmpty(someStack)) {
        struct node* newNode = (struct node*)malloc(sizeof(struct node));
        newNode->data = someData;
        newNode->next = someStack->head;
        someStack->head = (struct node*) newNode;
        return 0;
    }

    else if (someData < peek(someStack)) {
        struct node* newNode = (struct node*)malloc(sizeof(struct node));
        newNode->data = someData;
        newNode->next = someStack->head;
        someStack->head = (struct node*) newNode;
        return 0;
    }

    return (-1);

}


int main(){
    return 0;
}