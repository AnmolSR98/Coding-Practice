#include <stdio.h>
#include <stdlib.h>

// gonna have to search up how to do generics in C for this

struct node {
    void* firstData;
    void* secondData;
};

struct map {
    struct node* Nodes;
    int currentIndex;
    int length;
};

struct map* createMap(int size){

    struct map* newMap = (struct map*) malloc(size*sizeof(struct node));
    struct node nodesArray[size];
    newMap->Nodes = (struct node*) nodesArray;
    newMap->length = size;
    newMap->currentIndex = 0;

}

int size(struct map* someMap){
    return someMap->currentIndex;
}

int length(struct map* someMap){
    return someMap->length;
}

void addData(struct map* someMap, void* type1, void* type2) {
    
    if (length(someMap) == size(someMap)) {return (-1);}
 
    struct node* newNode = (struct node*) malloc(sizeof(struct node));
    newNode->firstData = type1;
    newNode->secondData = type2;
    someMap->Nodes[someMap->currentIndex] = newNode;
    someMap->currentIndex += 1;

}

void removeData(struct map* someMap, void* someData){
    
    if (someMap->currentIndex == 0) {return (-1);}
    
    int i;
    for (i = 0; i < someMap->currentIndex; i++) {
        if (someMap->Nodes[i] == someData){
            someMap->Nodes[i] = someMap->Nodes[someMap->currentIndex];
            someMap->currentIndex -= 1;
        }
    }

    return;
}

void* getData(struct map* someMap, void* someData){
    int i;
    for (i = 0; i < someMap->currentIndex; i++) {
        if (someMap->Nodes[i] == someData){
            return (struct node*) someMap->Nodes[i];
        }
    }

}