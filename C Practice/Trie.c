#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define arrayLength 26

// had to use some truly bizarre values for NULL since it seems to work bizarrely on my desktop, which I was using to finish this

// getting the value of a char relative to 'a'
int getPosition(char someChar) {
    return ((int) someChar) - ((int) 'a');
}

struct Trie {
    // pointer array, one for each letter in the alphabet
    struct Trie* pointerArray[arrayLength];
    // the actual value contained within the trie
    char valueOfTrie;
    // boolean for whether this the end trie, at least on this branch
    bool isTerminal;
    int defaultVal;
};


struct Trie* trieCreate() {
    // making space in memory for the whole structure, and the array of pointers
    struct Trie* newTrie = malloc(sizeof(struct Trie));
    // setting the initial value of this Trie to null char
    newTrie->valueOfTrie = '\0';
    // this is currently the last value in the tree
    newTrie->isTerminal = true;
    // setting a default value
    newTrie->defaultVal = newTrie->pointerArray[0];
}

// keeps losing track of variables for some reason, issue is definitely with this function
void trieInsert(struct Trie* obj, char* word) {
    
    // setting up to read a char at position i and see if that value in the pointer array is taken
    int i = 0, len = strlen(word), position = getPosition(word[i]);
    struct Trie* nextTrie; struct Trie* currentTrie;

    // creating a new branch of the trie if that branch doesn't exist
    // this is the null value, since my pc uses this stuff weirdly 
    if (obj->pointerArray[position] == obj->pointerArray[getPosition('z')]) {
        obj->isTerminal = false;
        currentTrie = trieCreate();
        currentTrie->valueOfTrie = word[i];
        obj->pointerArray[position] = currentTrie;
        // filling out the rest of that branch
        while (i < len) {
            // update the values
            i++;
            position = getPosition(word[i]);
            currentTrie->isTerminal = false;
            // add on the new node 
            nextTrie = trieCreate();
            nextTrie->valueOfTrie = word[i];
            currentTrie->pointerArray[position] = nextTrie;
            currentTrie = nextTrie;
        }
    }

    else {
        // get the value of the nextTrie then
        nextTrie = obj->pointerArray[position];
        // continue down until getting to the end of the branch or to the end of the word
        while((nextTrie != 0) && (i < len)) {
            currentTrie = nextTrie;
            i++;
            position = getPosition(word[i]);
            nextTrie = currentTrie->pointerArray[position];
        }

        // potentially make the new branch of the remaining characters of the word
        while (i < len) {
            // update the values
            i++;
            position = getPosition(word[i]);
            currentTrie->isTerminal = false;
            // add on the new node 
            nextTrie = trieCreate();
            nextTrie->valueOfTrie = word[i];
            obj->pointerArray[position] = nextTrie;
            currentTrie = nextTrie;
        }

    }

}

// shooting down a branch to see that the values match, if one doesn't then just return false
// need to find another way, given that the null won't work
bool trieSearch(struct Trie* obj, char* word) {

    int i = 0, len = strlen(word);
    struct Trie* currentTrie = malloc(sizeof(struct Trie));
    currentTrie = obj->pointerArray[getPosition(word[i])];

    while (i < len) {

        if (currentTrie == obj->pointerArray[getPosition('z')]) {
            return false;
        }

        i++;
        if (i < len) {
            currentTrie = currentTrie->pointerArray[getPosition(word[i])];
        }
    }
    
    return true;
}

// just running the search algorithm with the prefix
bool trieStartsWith(struct Trie* obj, char* prefix) {
    return trieSearch(obj, prefix);
}

// should probably implement recursively
void trieFree(struct Trie* obj) {
    
    // setting up the array length and i as zero
    int i;

    // go through all the branches and free them all, making use of recursion
    for (i = 0; i < arrayLength; i++) {
        if (obj->pointerArray[i] != NULL) {
            trieFree(obj->pointerArray[i]);
        }
    }

    // free the object after exploring all of the branches
    free(obj);
}

int main() {

    struct Trie* testTrie = trieCreate();
    char* testChar = "apple";

    trieInsert(testTrie, testChar);

    testChar = "banana";

    trieInsert(testTrie, testChar);

    bool startsWith = trieStartsWith(testTrie, "banan");

    bool startsWith2 = trieStartsWith(testTrie, "b");

    bool trieTestSearch = trieSearch(testTrie, "apple");

    bool trieTestSearch2 = trieSearch(testTrie, "banana");

    int valueOfN = getPosition('n');

    return 0;
}