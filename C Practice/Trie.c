#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


int getPosition(char someChar) {

    return ((int) someChar) - ((int) 'a');
}

typedef struct {
    // pointer array, one for each letter in the alphabet
    int* pointerArray;
    // the actual value contained within the trie
    char valueOfTrie;
    // boolean for whether this the end trie, at least on this branch
    bool isTerminal;

} Trie;


Trie* trieCreate() {
    // making space in memory for the whole structure, and the array of pointers
    Trie* newTrie = malloc(sizeof(Trie));
    newTrie->pointerArray = malloc(26*sizeof(int));
    // setting the initial value of this Trie to null char
    newTrie->valueOfTrie = '\0';
    // this is currently the last value in the tree
    newTrie->isTerminal = true;
}

void trieInsert(Trie* obj, char* word) {
    
    
}

bool trieSearch(Trie* obj, char* word) {
    
    return false;
}

bool trieStartsWith(Trie* obj, char* prefix) {
    
    return false;
}

void trieFree(Trie* obj) {
    
}