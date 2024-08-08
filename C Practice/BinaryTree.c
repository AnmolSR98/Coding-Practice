#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left, *right;
};

void addNode(int newData, struct node *root) {
    
    struct node *temp = root;
    printf("First");
    while (temp->data != 0){
        printf("Coolio");
        if (newData < temp->data){
            temp = temp->left;
        }

        else{
            temp = temp->right;
        }
    }

    struct node *newNode = (struct node *) malloc(sizeof(struct node)); 
    newNode->data = newData;

    temp = newNode;

    return;

}

int main() {

    struct node *testTree = (struct node *) malloc(sizeof(struct node));
    testTree->data = 50;
    printf("whatevs");
    addNode(48, testTree);
    printf("The value of the node is: %d\n", (testTree->left));
    return 0;
}
