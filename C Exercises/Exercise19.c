#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../Structures/BinaryTree.c"
#include "../Structures/SinglyLinkedList.c"

int getValueAtPosition(struct SinglyLinkedList* llist, int position) {

    struct node* temp = llist->head;
    int currentPos = 0;

    while (currentPos != position) {
        temp = temp->next;
        currentPos++;
    }

    return temp->data;
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
    int middle = (length - 1) / 2;
    int i;
    int currentNode = middle - 1;

    for (i = 0; i < middle; i++) {
        addNode(tree, getValueAtPosition(llist, i));
    }

    for (i = middle; i < length; i++) {

    }

}

int main() {

    int length = 5;
    int someList[5] = {-10, -3, 0, 5, 9};
    int i;

    struct SinglyLinkedList* test = (struct SinglyLinkedList*) malloc(sizeof(struct SinglyLinkedList));
    struct treeNode* testTree = (struct treeNode*) malloc(sizeof(struct treeNode));

    for (i = 0; i < length; i++) {
        add(test, someList[i]);
    }

    testTree = 
    

    return 0;
}