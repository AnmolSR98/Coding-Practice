#ifndef MAIN_H
#define MAIN_H

// include a bunch of standard c things, as well as the modified queue to be used for 
// both fifo and lru
#include <stdlib.h>
#include <stdbool.h>
#include "queue.c"

// generic largeNumber to be used for functions
#define largeNumber 10000000

// definition of page
typedef struct {
    int pageNumber;
    int dirty;
    int* reference;
} page;

// definition of frame 
typedef struct {
    // page that currently housed in said frame
    page* currentPage;
    
    // variables for the time the last process arrived, and when it will arrive next
    int timeArrived;
    int nextArrival;
} frame;    

// page creation method
page* createPage(char* pageNumber, char* dirty) {
    page* newPage = (page*) malloc(sizeof(page));
    
    newPage->pageNumber = atoi(pageNumber);
    newPage->dirty = atoi(dirty);

    return newPage;
}

// alternate one for the page table used in second chance
page* altCreatePage(int pageNumber, int n) {
    page* newPage = (page*) malloc(sizeof(page));
    
    newPage->pageNumber = pageNumber;

    // the array that simulates binary string for second chance
    newPage->reference = (int*) malloc(sizeof(int) * n);

    int i;
    for (i = 0; i < n; i++) {
        newPage->reference[i] = 0; 
    }

    return newPage;
}

// frame creation method
frame* createFrame(int frameId) {
    
    frame* newFrame = (frame*) malloc(sizeof(frame));

    newFrame->currentPage = NULL;
    newFrame->nextArrival = 0;

    return newFrame;
}

// strings to be used
char* divider = "+--------+-------------+-------------+\n";
char* header  = "| Frames | Page Faults | Write backs |\n";
char* content = "| %6d | %11d | %11d |\n";

// functions to actually use for printing the results of any given algorithm
void printHeader() {
    printf(divider);
    printf(header);
}

void printData(int x, int y, int z) {
    printf(divider);
    printf(content, x, y, z);
}

void printFooter() {
    printf(divider);
}

// more print functions to be used for the clock algorithm
char* clockDivider =  "+-----+-------------+-------------+\n";
char* clockHeaderN  = "|   n | Page Faults | Write backs |\n";
char* clockHeaderM  = "|   m | Page Faults | Write backs |\n";
char* clockContent =  "| %3d | %11d | %11d |\n";

void printClockHeaderN(){
    printf(clockDivider);
    printf(clockHeaderN);
}

void printClockData(int x, int y, int z) {
    printf(clockDivider);
    printf(clockContent, x, y, z);
}

void printClockHeaderM(){
    printf(clockDivider);
    printf(clockHeaderM);
}

void printClockFooter(){
    printf(clockDivider);
}

#endif

