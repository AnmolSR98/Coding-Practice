#include "main.h"

// look at write backs again for both FIFO and LRU
// definitely change, should only writeback for dirty bits

// function to the frame to update
// need to account for the page that will be doing the replacing
int getFrameToUpdateFIFO(frame** frameArray, int numFrames, int pageNumber) {

    int i;
    int oldestFrameIndex;
    int oldest = largeNumber;
    
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

        // check if that frame is the oldest, and if so, update it
        if (frameArray[i]->timeArrived < oldest) {
            oldest = frameArray[i]->timeArrived;
            oldestFrameIndex = i;
        }
    }

    // update the page fault if that specific page number was not found in memory
    frameArray[oldestFrameIndex]->pageFaults += 1;
    
    // if no free page was found then return the oldest frame
    return oldestFrameIndex;
}

int* fifo(page** pageArray, int numFrames, int numPages) {

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

        // gonna create a function to get the frame to update
        currentFrame = frameArray[getFrameToUpdateFIFO(frameArray, numFrames, newPage->pageNumber)];

        // update the time arrived value if the page was not already in the frame array
        if ((currentFrame->currentPage == NULL) || (currentFrame->currentPage->pageNumber != newPage->pageNumber)) {
            currentFrame->timeArrived = i;
        }

        if ((newPage->dirty == 1)) {
            currentFrame->totalWriteBacks += 1;
            totalWritebacks++;
        }

        if(currentFrame->currentPage!= NULL) {
            if (currentFrame->currentPage->pageNumber == newPage->pageNumber) {
                totalTimesWasInMemory++;
            }
        }

        // updating the frame with the new page
        currentFrame->currentPage = newPage;
    }

    //printTable(frameArray, numFrames);
    free(frameArray); 
    free(currentFrame); 
    //printf("%d\n", totalTimesWasInMemory);
    //printf("%d\n", totalWritebacks);

    int* returnData = (int*) malloc(sizeof(int)*2);
    returnData[0] = numPages-totalTimesWasInMemory; returnData[1] = totalWritebacks;

    return returnData;
}
