#include <stdio.h>
#include <stdlib.h>

// gonna have to search up how to do generics in C for this

struct node {
    char* firstData;
    int secondData;
    struct node* next;
};

struct map {
    struct node* head;
    int size;
};

struct map* createMap(){

    struct map* newMap = (struct map*) malloc(sizeof(struct map));
    newMap->size = 0;
}


void addData(struct map* someMap, char* type1, int type2) {
 
    struct node* newNode = (struct node*) malloc(sizeof(struct node));
    newNode->firstData = type1;
    newNode->secondData = type2;

    if (someMap->size == 0) {
        someMap->head = newNode;
    }

    else {
        struct node* temp = someMap->head;
        int i = 0;
        while (i < size(someMap)){
            temp = temp->next;
            i += 1;
        }

        temp->next = newNode;
    }

    someMap->size += 1;

}

void removeData(struct map* someMap, char* someData){
    
    if (someMap->size == 0) {return;}
    
    struct node* temp = someMap->head;
    struct node* nextNode = temp->next;

    while (nextNode != NULL) {

        if (someMap->firstData == someData){
            someMap->Nodes[i] = someMap->Nodes[someMap->currentIndex];
            someMap->currentIndex -= 1;
        }

        temp = nextNode;
        nextNode = next->next;

    }

    return;
}

int getData(struct map* someMap, char* someData){
    int i;
    while (i < someMap->size) {

        if (someMap->size == someData){
            return (struct node*) someMap->Nodes[i];
        }

        i += 1;
    }

}

int main(){

    struct map* test = createMap(10);
    addData(test, "Breakfast", (int) 10);
    printf("%d", getData(test, "Breakfast"));
    return 0;
}