#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../Structures/BinaryTree.c"
#include "../Structures/SinglyLinkedList.c"

int getMiddle(struct SinglyLinkedList* llist, int length) {

    if (length == 1) {
        struct node* temp = llist->head;
        int value = temp->data;
        free(temp);
        return value;
    }

    struct node* temp = llist->head;
    struct node* prev = NULL;
    int currentPos = 0;
    int middle = (length - 1) / 2;

    while (currentPos != middle) {
        prev = temp;
        temp = temp->next;
        currentPos++;
    }

    if (prev != NULL) {
        prev->next = temp->next;
    }

    else {
        llist->head = llist->head->next;
    }


    int value = temp->data;
    free(temp);

    return value;
}

int getLength(struct SinglyLinkedList* llist) {

    struct node* temp = llist->head;
    int length = 0;

    while( temp != NULL) {
        length++;
        temp = temp->next;
    }

    return length;
}

struct treeNode* sortedListToBST(struct SinglyLinkedList* llist){

    int length = getLength(llist);
    struct treeNode* tree =  (struct treeNode*) malloc( sizeof(struct treeNode) );
    int i;

    for (i = 0; i < length; i++) {
        getMiddle(llist, length - i);
    }

    return tree;

}

int main() {

    int length = 5;
    int someList[5] = {1, 2, 3, 4, 5};
    int i;

    struct SinglyLinkedList* test = (struct SinglyLinkedList*) malloc(sizeof(struct SinglyLinkedList));
    struct treeNode* testTree = (struct treeNode*) malloc(sizeof(struct treeNode));

    for (i = 0; i < length; i++) {
        add(test, someList[i]);
    }

    testTree = sortedListToBST(test);

    printTree(testTree);
    
    return 0;
}