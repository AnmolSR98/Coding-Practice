#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// gonna need to look at recursive functions for the bst from notes again

int getLeftChild(int index) {
    return 2*index + 1;
}

int getRightChild(int index) {
    return 2*index + 2;
}

bool recCheckTree(int* array, int root) {

    if (array[root] == NULL) {
        return true;
    }

    else if ((array[root] < array[getRightChild(root)]) && (array[root] > array[getLeftChild(root)])) {
        recCheckTree(array, getLeftChild(root)); 
        recCheckTree(array, getRightChild(root));   
    }

    else {
        return false;
    }

    return true;
}

// function for checking if the tree is a valid binary search tree (for preorder traversal)
bool isValidBST(int* tree) {
    return recCheckTree(tree, 0);
}


int main() {
    
    int testTree[7] = {5, 2, 7, 1, 4, 6, 10};
    bool test = isValidBST(testTree);
    return 0;
}