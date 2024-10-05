#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdbool.h>

#define largeNumber 10000000

typedef struct {
    int pageNumber;
    int dirty;
    int* reference;
} page;

typedef struct {
    page* currentPage;
    int totalWriteBacks;
    int frameId; 
    int pageFaults;
    int timeArrived;
} frame;    

page* createPage(char* pageNumber, char* dirty) {
    page* newPage = (page*) malloc(sizeof(page));
    
    newPage->pageNumber = atoi(pageNumber);
    newPage->dirty = atoi(dirty);

    return newPage;
}

page* altCreatePage(int pageNumber, int n) {
    page* newPage = (page*) malloc(sizeof(page));
    
    newPage->pageNumber = pageNumber;
    newPage->reference = (int*) malloc(sizeof(int) * n);

    int i;
    for (i = 0; i < n; i++) {
        newPage->reference[i] = 0; 
    }

    return newPage;
}

frame* createFrame(int frameId) {
    frame* newFrame = (frame*) malloc(sizeof(frame));

    newFrame->currentPage = NULL;
    newFrame->frameId = frameId;
    newFrame->pageFaults = 0;
    newFrame->totalWriteBacks = 0;

    return newFrame;
}

char* divider = "+--------+-------------+-------------+\n";
char* header  = "| Frames | Page Faults | Write backs |\n";
char* content = "| %6d | %11d | %11d |\n";

void printTable(frame** frameArray, int numFrames) {

    printf(divider);
    printf(header);
    printf(divider);

    frame* currentFrame = malloc(sizeof(frame));

    int i;
    for (i = 0; i < numFrames; i++) {
        currentFrame = frameArray[i];
        printf(content, currentFrame->frameId, currentFrame->pageFaults, currentFrame->totalWriteBacks);
        if (i < numFrames - 1) { 
            printf(divider);
        }
    }

    printf(divider);
    free(currentFrame);
}

#endif

