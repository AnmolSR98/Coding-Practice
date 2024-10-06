#include "main.h"
#include "math.h"
#include <stdio.h>

// definitely some issue with this here

// had forgotten to implement this
void setMostSignificantBit(int* someArray) {
    someArray[0] = 1;
}

int getTotalValue(int* someArray, int length) {
    int i, arraySum = 0;
    for (i = 0; i < length; i++) {
        arraySum += someArray[i]*pow(10, length - i - 1);
    }

    return arraySum;
}

// only works for one shift, which ought to be needed for this assignment
int* logicalShiftRight(int* someArray, int length) {
    int i;
    int holder = someArray[0];
    int holder2 = someArray[0];
    for (i = 1; i < length; i++) {
        holder = holder2;
        holder2 = someArray[i];
        someArray[i] = holder;
    }

    someArray[0] = 0;

    return someArray;
}

void updatePageTable(page** pageTable, int numUniquePages, int n) {
    
    int i, j;
    for (i = 0; i < numUniquePages; i++) {
        logicalShiftRight(pageTable[i]->reference, n);
    }
}

// need to change this function to return the frame containing the page with the smallest array sum 
// function to the frame to update

int getFrameToUpdateSecond(frame** frameArray, page** pageArray, page** pageTable, int numFrames, int numPages, int numUniquePages, int pageNumber, int n) {

    int i;
    int frameIndex = 0;
    int smallestVal = largeNumber;
    int potential;
    page* somePage = (page*) malloc(sizeof(page));
    
    // loop to cycle through the various frames to see if any of them are free
    for (i = 0; i < numFrames; i++) {
        // return if one is found
        if (frameArray[i]->currentPage == NULL) {
            frameArray[i]->pageFaults += 1;
            return i;
        }
        // otherwise if the page is already in memory return it
        else if (frameArray[i]->currentPage->pageNumber == pageNumber) {
            return i;
        }

        somePage = frameArray[i]->currentPage;
        potential = getTotalValue(pageTable[somePage->pageNumber]->reference, n);

        // check to see if this page has the smallest reference in the table, and if so update it
        if (potential < smallestVal) {
            frameIndex = i;
            smallestVal = potential;
        }

    }

    // update the page fault if that specific page number was not found in memory
    frameArray[frameIndex]->pageFaults += 1;
    
    // if no free page was found then return the frame with the lowest reference value
    return frameIndex;
}

// need to change this so that it performs the shift right every m number of frames
int* secondChance(page** pageArray, int numFrames, int numPages, int m, int n, int numUniquePages) {

    // creating a new array of frames and filling it
    frame** frameArray = (frame**) malloc(sizeof(frame) * numFrames);
    int i;
    for (i = 0; i < numFrames; i++) {
        frameArray[i] = createFrame(i+1);
    }

    page** pageTable = (page**)  malloc(sizeof(page) * numUniquePages);
    for (i = 0; i < numUniquePages; i++) {
        pageTable[i] = altCreatePage(i, n);
    }

    int frameToUpdate;
    page* newPage = (page*) malloc(sizeof(page));
    frame* currentFrame = (frame*) malloc(sizeof(frame));
    int totalTimesWasInMemory = 0;
    int totalWritebacks = 0;

    // now moving onto actually simulating checking the frames
    for (i = 0; i < numPages; i++) {

        // get the current page from the queue
        newPage = pageArray[i];

        // gonna create a function to check for the index of the first free frame
        int newThing = getFrameToUpdateSecond(frameArray, pageArray, pageTable, numFrames, numPages, numUniquePages, newPage->pageNumber, n);
        currentFrame = frameArray[newThing];

        // adding on a update if the frame was null before or if the current page has a dirty bit
        // in the case of a null frame or change in page number, add on a write back

        // also do this in the case for identical page numbers but with a dirty bit
        if ((newPage->dirty == 1)) {
            currentFrame->totalWriteBacks += 1;
            totalWritebacks++;
        }

        if(currentFrame->currentPage!= NULL) {
            if (currentFrame->currentPage->pageNumber == newPage->pageNumber) {
                totalTimesWasInMemory++;
            }
        }

        // updating the frame
        currentFrame->currentPage = newPage;
        setMostSignificantBit(pageTable[newPage->pageNumber]->reference);

        if (i % m == 0) {
            updatePageTable(pageTable, numUniquePages, n);
        }
    }

    printTable(frameArray, numFrames);
    //printf("%d\n", totalTimesWasInMemory);
    free(pageTable); free(frameArray); free(newPage);

    int* returnData = (int*) malloc(sizeof(int)*2);
    returnData[0] = numPages-totalTimesWasInMemory; returnData[1] = totalWritebacks;

    return returnData;
}