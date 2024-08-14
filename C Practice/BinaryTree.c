#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left, *right;
};

void addNode(int newData, struct node *root) {
    
    struct node *temp = root;
    printf("First\n");
    struct node *newNode = (struct node *) malloc(sizeof(struct node));
    newNode->data = 46;
    temp->left = newNode;

    if (temp->right == NULL){
        printf("right is uninitialized\n");
    }

    return;

}

int main() {

    struct node *testTree = (struct node *) malloc(sizeof(struct node));
    testTree->data = 50;
    printf("whatevs\n");
    addNode(48, testTree);
    printf("The value of the node is: %d\n", (testTree->left->data));
    return 0;
}
