#include <stdlib.h>
#include <stdio.h>

// directory itself can be either a linear list or hashtable

// contiguous is kinda self explanatory

struct linkedAlloc {
    struct indexedAlloc nextNode;
    int data;
};

struct indexedAlloc {
    int* pointerTable; // where each of the pointers point to disk blocks
                        // of course one block min has to be allocated to store this information
};

struct twoLevelIndex {
    int** pointerTable; // where each of the pointers point to another index table, which then points to disk blocks
                        // of course one block min has to be allocated to store this information
};

// now onto free space management
struct node {
    int data;
    struct node next;
};

// for linked list of free space management
struct freeSpaceLinked {
    struct node head;
    int size;
};

// for counting
struct freeSpaceCounting {

};