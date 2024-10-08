#include "main.h"

// function that finds index of first instance of the pageNumber
int indexOfNextInstance(page** pageArray, int lowerBound, int length, int pageNumber) {

    int i;
    // cycle through and return the very first instance of the page number
    for (i = lowerBound + 1; i < length; i++) {

        if (pageArray[i]->pageNumber == pageNumber) {
            return i;
        }
    }
    
    // return -1 if the page doesn't show up again
    return (-1);
}

int getFrameToUpdateOptimal(frame** frameArray, page** pageArray, int numFrames, int numPages, int pageNumber, int currentIndex) {

    int i;
    int frameIndex = 0;
    int latest = 0;
    int potential;
    
    // loop to cycle through the various frames to see if any of them are free
    for (i = 0; i < numFrames; i++) {

        // return if one is found
        if (frameArray[i]->currentPage == NULL) {
            frameArray[i]->pageFaults += 1;
            return i;
        }

        else if (frameArray[i]->currentPage->pageNumber == pageNumber) {
            return i;
        }

        // check if the page in the frame appears that last, or not at all
        potential = frameArray[i]->nextArrival;

        // if it appears last or doesn't appear at all, then this is the frame to update
        if ((potential > latest) || ((potential == -1) && (latest != -1))) {
            latest = potential;
            frameIndex = i;
        }
    }

    // update the page fault if that specific page number was not found in memory
    frameArray[frameIndex]->pageFaults += 1;
    
    // if no free page was found then return the frame with the page that will reappear last or not at all
    return frameIndex;
}

int* optimal(page** pageArray, int numFrames, int numPages) {

    // creating a new array of frames and filling it
    frame** frameArray = malloc(sizeof(frame) * numFrames);
    int i;
    for (i = 0; i < numFrames; i++) {
        frameArray[i] = createFrame(i+1);
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
        currentFrame = frameArray[getFrameToUpdateOptimal(frameArray, pageArray, numFrames, numPages, newPage->pageNumber, i)];

        // adding on a update if the frame was null before or if the current page has a dirty bit
        // in the case of a null frame or change in page number, add on a write back

        // writing back to memory if current page is dirty 
        if (currentFrame->currentPage != NULL) {
            if (currentFrame->currentPage->dirty == 1) {
                totalWritebacks++;
            }
        }
        
        if(currentFrame->currentPage!= NULL) {
            if (currentFrame->currentPage->pageNumber == newPage->pageNumber) {
                totalTimesWasInMemory++;
            }
        }

        // updating the frame
        currentFrame->currentPage = newPage;
        currentFrame->nextArrival = indexOfNextInstance(pageArray, i, numPages, currentFrame->currentPage->pageNumber);
    }

    //printTable(frameArray, numFrames);
    free(frameArray); free(currentFrame);
    //printf("%d\n", totalTimesWasInMemory);
    //printf("%d\n", totalWritebacks);

    int* returnData = (int*) malloc(sizeof(int)*2);
    returnData[0] = numPages-totalTimesWasInMemory; returnData[1] = totalWritebacks;

    return returnData;
}
