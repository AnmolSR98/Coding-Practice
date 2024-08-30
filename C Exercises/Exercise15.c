#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../Structures/SinglyLinkedList.c"

// to swap the values of a node
void swapValues(struct node* someNode, struct node* otherNode) {

    int holder = someNode->data;
    someNode->data = otherNode->data;
    otherNode->data = holder;
}

// making a function to go through a function to swap nodes in pair
void swapPairs(struct SinglyLinkedList* slList) {

    struct node* first = slList->head;
    struct node* second;
    
    while (first != NULL) {
        second = first->next;

        if (second != NULL) {
            swapValues(first, second);
            first = second->next;
        }

        else {
            first = first->next;
        }
    }
}

int main(){

    int length = 7;
    int test[7] = {1, 3, 5, 7, 9, 11, 13};
    struct SinglyLinkedList* testList = malloc(sizeof(struct SinglyLinkedList));

    int i;
    for (i = 0; i < length; i++) {
        add(testList, test[i]);
    }  

    printSLL(testList);
    swapPairs(testList);
    printSLL(testList);

    return 0;
}