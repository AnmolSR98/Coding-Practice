#include "main.h"

// look at write backs again for both FIFO and LRU
// definitely change, should only writeback for dirty bits

// function to the frame to update
// need to account for the page that will be doing the replacing
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
        potential = indexOfNextInstance(pageArray, currentIndex, numPages, frameArray[i]->currentPage->pageNumber);

        if ((potential > latest) || ((potential == -1) && (latest != -1))) {
            latest = potential;
            frameIndex = i;
        }
    }

    // update the page fault if that specific page number was not found in memory
    frameArray[frameIndex]->pageFaults += 1;
    
    // if no free page was found then return the oldest frame
    return frameIndex;
}

void optimal(page** pageArray, int numFrames, int numPages) {

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

        // also do this in the case for identical page numbers but with a dirty bit
        if ( (newPage->dirty == 1)) {
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
    }

    //printTable(frameArray, numFrames);
    free(frameArray); free(currentFrame); free(newPage); 
    //printf("%d\n", totalTimesWasInMemory);
    //printf("%d\n", totalWritebacks);

    int* returnData = (int*) malloc(sizeof(int)*2);
    returnData[0] = numPages-totalTimesWasInMemory; returnData[1] = totalWritebacks;

    return returnData;
}
