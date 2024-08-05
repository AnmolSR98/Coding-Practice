#include <stdio.h>

struct node {
    int data;
    struct node *left;
    struct node *right;
};

struct binarySearchTree {
    struct node root;
};

int main() {
    struct node testNode = {50, NULL, NULL};
    struct binarySearchTree testTree = {testNode};
    printf("The value of the node is: %d\n", testTree.root);
    return 0;
}