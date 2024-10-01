#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>

typedef struct {
    int pageNumber;
    int dirty;
} page;

typedef struct {
    page* currentPage;
    int totalWriteBacks; 
} frame;    

page* createPage(char* pageNumber, char* dirty) {
    page* newPage = (page*) malloc(sizeof(page));
    
    newPage->pageNumber = atoi(pageNumber);
    newPage->dirty = atoi(dirty);

    return newPage;
}

frame* createFrame() {
    frame* newFrame = (frame*) malloc(sizeof(frame));

    newFrame->currentPage = NULL;
    newFrame->totalWriteBacks = 0;

    return newFrame;
}

#endif

