#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left, *right;
};

// add node code
void addNode(int newData, struct node *root) {
    
    // getting two node pointers, one which stores the immediate value, one for the one before 
    struct node *temp = root;
    struct node *next = temp;

    // take the last node that is not null to store as temp 
    while (next != NULL) {
        if (newData < next->left){
            temp = next;
            next = next->left;
        }

        else {
            temp = next;
            next = next->right;
        }
    }

    // construct a new node
    struct node *newNode = (struct node *) malloc(sizeof(struct node));
    newNode->data = newData;

    // place it in either left or right depending on the value
    if (newData < temp->data){
        temp->left = newNode;
    }

    else {
        temp->right = newNode;
    }

    // end void
    return;
}

// use recursive in order traversal
int size(struct node *root){
    return 0;
}struct node *getPredecessor(struct node *root, int nodeValue){
    return;
}

// use recursive in order traversal
int contains(struct node *root){
    return 0;
}

// traverse down a specific path to get the value
struct node *getPredecessor(struct node *root, int nodeValue){
    return;
}


struct node *getSuccecessor(struct node *root, int nodeValue){
    return;
}

void deleteNode(struct node *root, int nodeValue){
    return;
}

int main() {

    // just some test code to ensure this works
    struct node *testTree = (struct node *) malloc(sizeof(struct node));
    testTree->data = 50;
    addNode(46, testTree);
    printf("The value of the node is: %d\n", (testTree->left->data));
    return 0;
}
