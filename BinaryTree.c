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

struct node *getPredecessor(struct node *root){
    
    struct node* temp = root;
    struct node* next = root;

    next = next->left;

    if (next != NULL){
        while (next->right != NULL){
            next = next->right;
        }
    }

    return next;
}


struct node *getSuccessor(struct node *root){
    
    struct node* temp = root;
    struct node* next = root;

    next = next->right;

    if (next != NULL){
        while (next->left != NULL){
            next = next->left;
        }
    }

    return next;
}

void deleteNode(struct node *root, int targetValue){

    if (!contains(root, targetValue)){
        printf("Value is not in the tree!\n");
        return;
    }

    // case where the root is targeted
    if (targetValue == root->data) {

        struct node *successor = getSuccessor(root);
        struct node *predecessor = getPredecessor(root);

        // case where no successor exists
        if (successor == NULL) {
             if (predecessor == NULL) {
                 root->data == NULL;
             }

             else {
                 root->data = root->left->data;
                 root->left = NULL;
             }

             
        }
        successor->left = root->left;

        printf("%d", successor->data);

        if (root->right != successor){
            successor->right = root->right;
        } 

        root->data = successor->data;

        return;
    }

    struct node *parent = root;
    struct node *next = root;
    int child = 0;

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

    if ((next->left == NULL) && (next->right == NULL)) {
        if (!child){
            parent->left = NULL;
        }

        else{
            parent->right = NULL;
        }
    }

    else if (getSuccessor(next) == NULL){
        if (!child) {
            parent->left = next->left;
        }

        else{
            parent->right = next->left;
        }
    }
 
    else {
        if (!child) {
            parent->left = successor;
        }

        else{
            parent->right = successor;
        }

        successor->left = next->left;

        if (next->right != successor){
            successor->right = next->right;
        }   
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
    printf("Does it contain %d? %d\n", 50, contains(testTree, 50));
    deleteNode(testTree, 50);
    printf("Does it contain %d? %d\n", 50, contains(testTree, 50));
    printf("%d", testTree->data);
    //printTree(testTree);
    return 0;
}
