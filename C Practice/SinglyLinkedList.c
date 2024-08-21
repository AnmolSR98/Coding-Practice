#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node* next;
};

struct SinglyLinkedList{
    struct node* head;
};

int isEmpty(struct SinglyLinkedList* llist){
    if (llist->head == NULL) {
        return 1;
    }

    return 0;
}

int isFull(struct SinglyLinkedList* llist){
    return 0;
}

void add(struct SinglyLinkedList* llist, int dataToAdd){

    struct node* newNode = (struct node*) malloc(sizeof(struct node));
    newNode->data = dataToAdd;
    
    if (isEmpty(llist)){
        llist->head = newNode;
    }

    else {
        struct node* temp = llist->head;
        while (temp->next != NULL){
            temp = temp->next;
        }

        temp->next = newNode;
    }

    return;
}

int pop(struct SinglyLinkedList* llist) {

    if (isEmpty(llist)){
        return NULL;
    }

    struct node* temp = llist->head;
    int returnData = temp->data;
    llist->head = llist->head->next;
    free(temp);
    return returnData;
}