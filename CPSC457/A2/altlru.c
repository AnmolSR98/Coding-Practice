#include "main.h"

// look at write backs again for both FIFO and LRU
// definitely change, should only writeback for dirty bits

// function to the frame to update
// need to account for the page that will be doing the replacing
int getFrameToUpdateAltLRU(frame** frameArray, int numFrames, int pageNumber, int nextInQueue) {

    int i;
    int frameToReplace = -1;
    
    // loop to cycle through the various frames to see if any of them are free
    for (i = 0; i < numFrames; i++) {
        // return if one is found
        if (frameArray[i]->currentPage == NULL) {
            return i;
        }

        // return if it is already in memory
        else if (frameArray[i]->currentPage->pageNumber == pageNumber) {
            return i;
        }

        // hang to the index of the frame if it contains the process that is next in the queue
        else if (frameArray[i]->currentPage->pageNumber == nextInQueue) {
            frameToReplace = i;
        }
    }

    // if the frame is there to replace, replace it
    if (frameToReplace != -1) {
        return frameToReplace;
    }

    // in the case that no frame can be updated, should never happen
    return (-1);
}

int* altLRU(page** pageArray, int numFrames, int numPages) {

    // creating a new array of frames and filling it
    frame** frameArray = malloc(sizeof(frame) * numFrames);
    int i;
    for (i = 0; i < numFrames; i++) {
        frameArray[i] = createFrame(i+1);
    }


    page* newPage = (page*) malloc(sizeof(page));
    frame* currentFrame = (frame*) malloc(sizeof(frame));
    queue* someQueue = createQueue();
    int totalWritebacks = 0;
    int totalPageFaults = 0;
    int nextInQueue = -1;
    int frameToGet;

    // now moving onto actually simulating checking the frames
    for (i = 0; i < numPages; i++) {

        // get the current page from the queue
        newPage = pageArray[i];

        // get the number of the next page to be replaced
        if (!isEmpty(someQueue)) {
            nextInQueue = someQueue->head->data;
        }

        // gonna create a function to get the frame to update
        frameToGet = getFrameToUpdateAltLRU(frameArray, numFrames, newPage->pageNumber, nextInQueue);
        currentFrame = frameArray[frameToGet];

        if (currentFrame->currentPage != NULL) {
            // writing back to memory if current page is dirty 
            if (currentFrame->currentPage->dirty == 1) {
                totalWritebacks++;
            }

            if (currentFrame->currentPage->pageNumber != newPage->pageNumber) {
                totalPageFaults++;
                // if this page was not already in memory then it must be added to the queue
                dequeue(someQueue);
                enqueue(someQueue, newPage->pageNumber);
            }

            // if the page is memory, then remove it from the queue and add it again, so the
            // least recently used frame will move to the front
            else {
                removeFromQueue(someQueue, newPage->pageNumber);
                enqueue(someQueue, newPage->pageNumber);
            }

        }

        else {
            totalPageFaults++;
            enqueue(someQueue, newPage->pageNumber);
        }

        // updating the frame with the new page
        currentFrame->currentPage = newPage;
    }

    free(frameArray); 
    free(currentFrame); 

    int* returnData = (int*) malloc(sizeof(int)*2);
    returnData[0] = totalPageFaults; returnData[1] = totalWritebacks;

    return returnData;
}