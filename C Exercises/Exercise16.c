#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../Structures/SinglyLinkedList.c"

// quick function to get the size of a singly linked list
int getSLLSize(struct SinglyLinkedList* sLList) {

    int n = 0;
    struct node* temp = sLList->head;
    while (temp != NULL) {
        n++;
        temp = temp->next;
    }

    return n;
}

// assuming 1 would mean get last
void removeNthFromLast(struct SinglyLinkedList* sLList, int n) {

    // first get the length
    int length = getSLLSize(sLList);

    // error case
    if ((n < 1) || (n > length)) {
        return;
    }

    // base case for the first 
    if (n == length) {
        struct node* toFree = sLList->head;
        sLList->head = sLList->head->next;
        free(toFree);
        return;
    }

    // get the current as the head, set the prev to null
    struct node* current = sLList->head, *prev;

    int i;
    // cycle through to the node needed
    for (i = 0; i < length - n; i++) {
        prev = current;
        current = current->next;
    }

    // break the link and link the next node to the previous node, then free the current node from memory
    prev->next = current->next;
    free(current);

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

    removeNthFromLast(testList, 4);

    printSLL(testList);

    return 0;
}
