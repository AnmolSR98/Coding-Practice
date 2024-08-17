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
    struct node *next = root;

    // take the last node that is not null to store as temp 
    while (next != NULL) {
        if (newData < next->data){
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

void printTree(struct node *root){

    if (root != NULL){

        printTree(root->left);
        printf("%d\n", root->data);
        printTree(root->right);
    }

    return;
}

// use recursive in order traversal
int size(struct node *root){
    
    if (root == NULL){
        return 0;
    }

    return size(root->left) + 1 + size(root->right);
}

// use recursive in order traversal
int contains(struct node *root, int targetValue){
    if (root == NULL) {
        return 0;
    }

    else {
        if (root->data == targetValue){
            return 1;
        }

        else if (root->data > targetValue){
            return contains(root->left, targetValue);
        }

        else{
            return contains(root->right, targetValue);
        }
    }


}

struct node *getChild(struct node *root){
    if (root->left != NULL){
        return root->left;
    }

    return root->right;
}

// both of the following functions also detach, so be careful in use
struct node *getPredecessor(struct node *root){

    struct node* next = root;
    int child = 0;
    struct node* parent = next;
    next = next->left;

    if (next != NULL){
        while (next->right != NULL){
            parent = next;
            next = next->right;
            child = 0;
        }
    }

    if (child == 0){
        parent->left = NULL;
    }

    else{
        parent->right = NULL;
    }


    return next;
}

struct node *getSuccessor(struct node *root){
    
    struct node* next = root;
    int child = 1;
    struct node* parent = next;
    next = next->right;

    if (next != NULL){

        while (next->left != NULL){
            parent = next;
            next = next->left;
            child = 0;
        }
    }

    if (child == 0){
        parent->left = NULL;
    }

    else{
        parent->right = NULL;
    }

    return next;
}

// majorly fix this up, still needs a polish for when the root is deleted and only has a left child
void deleteNode(struct node *root, int targetValue){

    struct node *parent = NULL;
    struct node *next = root;
    int child = 0;

    if (!contains(root, targetValue)){
        return;
    }

    // take the last node that is not null to store as temp 
    while (next->data != targetValue) {

        if (targetValue < next->data){
            parent = next;
            next = next->left;
            child = 0;
        }

        else {
            parent = next;
            next = next->right;
            child = 1;
        }
    }

    struct node *successor = getSuccessor(next);

    // case where the node is the root
    if (parent == NULL){

        printf("1\n");
        if (successor != NULL) {
            next->data = successor->data;
            successor->right = next->right;
        }

        else {
            struct node* predecessor = getPredecessor(next);

            if (predecessor != NULL) {
                next->data = predecessor->data;
                predecessor->left = next->left;
            }

            // case where the node ends being a singleton
            else{
                next = NULL;
            }
        }
    }

    // case where the node has no successor
    else if (successor == NULL){

        printf("2\n");
        struct node* predecessor = getPredecessor(next);

        if (predecessor != NULL){
            next->data = predecessor->data;
        }

        // case without predecessor, ie. it is a leaf
        else {
            if (child == 0) {
                parent->left = NULL;
            }

            else{
                parent->right = NULL;
            }
        }
    }

    // has a successor
    else {
        printf("3\n");
        next->data = successor->data;
    }

    return;
}

int main() {

    // just some test code to ensure this works
    struct node *testTree = (struct node *) malloc(sizeof(struct node));
    testTree->data = 50;
    addNode(46, testTree);
    addNode(56, testTree);
    addNode(60, testTree);
    addNode(52, testTree);
    printTree(testTree);
    printf("The size of the tree is: %d\n", size(testTree));

    int delete = 60;
    printf("Does it contain %d? %d\n", delete, contains(testTree, delete));
    deleteNode(testTree, delete);
    printf("Does it contain %d? %d\n", delete, contains(testTree, delete));
    printTree(testTree);

    delete = 56;
    printf("Does it contain %d? %d\n", delete, contains(testTree, delete));
    deleteNode(testTree, delete);
    printf("Does it contain %d? %d\n", delete, contains(testTree, delete));
    printTree(testTree);

    delete = 50;
    printf("Does it contain %d? %d\n", delete, contains(testTree, delete));
    deleteNode(testTree, delete);
    printf("Does it contain %d? %d\n", delete, contains(testTree, delete));
    printTree(testTree);
    return 0;
}