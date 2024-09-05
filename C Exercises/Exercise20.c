// code for deleting duplicates from a sorted list, only we are deleting all instances of that number within that list
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Structures/SinglyLinkedList.c"

// check that there are multiples by cycling through, checking if there at least two instances, returning true after finding second instance
bool hasMultiplesOf(struct SinglyLinkedList* someList, int val) {

    struct node* temp = someList->head;
    bool hasAPreviousInstance = false;

    while (temp != NULL) {
        
        if (temp->data == val) {
            
            if (hasAPreviousInstance) {
                return true;
            }

            else {
                hasAPreviousInstance = true;
            }
        }

        temp = temp->next;
    }

    return false;
}

// removes all instances of an integer
struct node* removeAllInstancesOf(struct SinglyLinkedList* someList, int val) {

    // should return the new head back 
    struct node* temp = someList->head;
    struct node* prev;
    struct node* toFree;

    while (temp != NULL) {

        if (temp->data == val) {

            // ie. the head is the value earmarked to be removed
            if (temp == someList->head) {
                // shuffle the head forward and continue on, leaving prev as uninitialized
                toFree = temp;
                someList->head = someList->head->next;
                temp = someList->head;
                free(toFree);
            }

            // ie. the node is not the head
            else {
                // break around the node
                prev->next = temp->next;
                toFree = temp;
                temp = temp->next;
                free(toFree);
            }

        }

        else {
            // if not the value, just keep chooglin' along
            prev = temp;
            temp = temp->next;
        }
    }

    return someList->head;

}

// actual function used that cycles through the list, removing them if there are duplicates
void removeAllDuplicates(struct SinglyLinkedList* someList){

    struct node* temp = someList->head;

    while (temp != NULL) {

        if (hasMultiplesOf(someList, temp->data)) {
            temp = removeAllInstancesOf(someList, temp->data);
        }

        else {
            temp = temp->next;
        }
    }
}


int main() {

    int length = 8;
    int test[8] = {1, 1, 2, 2, 7, 7, 7, 13};
    struct SinglyLinkedList* testList = malloc(sizeof(struct SinglyLinkedList));

    int i;
    for (i = 0; i < length; i++) {
        add(testList, test[i]);
    }  

    struct node* testNode = testList->head;
    for (i = 0; i < length; i++) {
        printf("%d ", hasMultiplesOf(testList, testNode->data));
        testNode = testNode->next;
    }
    printf("\n");  

    printSLL(testList);

    removeAllDuplicates(testList);

    printSLL(testList);

    return 0;
}