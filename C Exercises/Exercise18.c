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

// check that the root is greater than its predecessor
bool checkPredecessor(int* array, int root, int length) {

    int successor = getLeftChild(root);
    bool loop = true;

    while (loop) {
        if (getRightChild(successor) < length) {
            successor = getRightChild(successor);
        }

        else {
            loop = false;
        }
    }

    return (array[root] > array[successor]);
}

// check that the root is less than its successor
bool checkSuccessor(int* array, int root, int length) {

    int predecessor = getRightChild(root);
    bool loop = true;

    while (loop) {

        if (getLeftChild(predecessor) < length) {
            predecessor = getLeftChild(predecessor);
        }

        else {
            loop = false;
        }
    }

    return (array[root] < array[predecessor]);
}

bool recCheckTree(int* array, int root, int length) {

    // if the array is null, return true
    if (array[root] == 0) {
        return true;
    }

    // otherwise
    else {

        // if both the children are null, return true
        if ((getLeftChild(root) >= length) && (getRightChild(root) >= length)){
            return true;
        }
        
        // if the left child is null
        else if ((getLeftChild(root) >= length)) {
            
            // check the right child
            if (array[root] < array[getRightChild(root)]) {
                return recCheckTree(array, getRightChild(root), length);
            }
        }

        // if the right child is null
        else if ((getRightChild(root) >= length)) {
            
            // check the left child
            if (array[root] > array[getLeftChild(root)]) {
                return recCheckTree(array, getLeftChild(root), length);
            }
        }

        // otherwise if it has both children, check that the condition is upheld
        else if ((array[root] > array[getLeftChild(root)]) && (array[root] < array[getRightChild(root)])) {
            return recCheckTree(array, getLeftChild(root), length) && recCheckTree(array, getRightChild(root), length);
        }
    }

    return false;
}

// function for checking if the tree is a valid binary search tree (for preorder traversal)
bool isValidBST(int* tree, int length) {
    return recCheckTree(tree, 0, length) && checkPredecessor(tree, 0, length) && checkSuccessor(tree, 0, length);
}


int main() {
    
    int length = 7;
    int testTree[7] = {7, 3, 9, 2, 4, 8, 10};
    bool test = isValidBST(testTree, length);
    return 0;
}