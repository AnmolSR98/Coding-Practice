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
    struct binarySearchTree testTree;
    testTree.root = testNode;
    printf("The value of the node is: %d\n", testTree.root.data);
    return 0;
}