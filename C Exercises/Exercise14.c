// code for adding all the elements of two linked lists together, with their sums only represented by last digit (ie. modulo by 10)
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Structures/SinglyLinkedList.c"

// function to get the sum values of two node's data
int getSum(struct node* someNode, struct node* otherNode) {

    if ((someNode == NULL) && (otherNode != NULL)) {
        return otherNode->data;
    }

    else if ((someNode != NULL) && (otherNode == NULL)) {
        return someNode->data;
    }

    else {
        return (someNode->data + otherNode->data);
    }
}

struct SinglyLinkedList* addTwoNumbers(struct SinglyLinkedList* l1, struct SinglyLinkedList* l2) {
    
    struct node* temp1 = l1->head;
    struct node* temp2 = l2->head;
    struct SinglyLinkedList* newList = malloc(sizeof(struct SinglyLinkedList));
    bool carryBit = false;
    int newVal;

    while ((temp1 != NULL) || (temp2 != NULL)) {

        // get the values summed together
        newVal = getSum(temp1, temp2);

        // if there is a carry bit from the previous operation, add it on
        if (carryBit) {
            newVal += 1;
        }

        // check if this newVal should result in a carry bit for the next operation
        if (newVal >= 10) {
            carryBit = true;
        }

        else {
            carryBit = false;
        }

        // actually add the new value
        add(newList, newVal % 10);

        // post operation updating of list values
        if (temp1 != NULL) {
            temp1 = temp1->next;
        }

        if (temp2 != NULL) {
            temp2 = temp2->next;
        }

        // final operation in case there is a carry bit on the last node
        if ( (temp1 == NULL) && (temp2 == NULL) && (carryBit) ) {
            add(newList, 1);
        }
    }

    return newList;
}

int main(){

    int array1[7] = {2, 4, 3};
    int length1 = 3;
    int array2[4] = {5, 6, 4};
    int length2 = 3;
    struct SinglyLinkedList* list1 = malloc(sizeof(struct SinglyLinkedList));
    struct SinglyLinkedList* list2 = malloc(sizeof(struct SinglyLinkedList));

    int i;
    for (i = 0; i < length1; i++) {
        add(list1, array1[i]);
    }

    for (i = 0; i < length2; i++) {
        add(list2, array2[i]);
    }

    struct SinglyLinkedList* new = addTwoNumbers(list1, list2);
    printSLL(new);

    return 0;
}