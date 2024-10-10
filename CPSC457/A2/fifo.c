#include "main.h"


// function to get the frame to update
int getFrameToUpdateFIFO(frame** frameArray, int numFrames, int pageNumber, int nextInQueue) {

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

int* fifo(page** pageArray, int numFrames, int numPages) {

    // creating a new array of frames and filling it
    frame** frameArray = malloc(sizeof(frame) * numFrames);
    int i;
    for (i = 0; i < numFrames; i++) {
        frameArray[i] = createFrame(i+1);
    }

    // creating pointers for the next page and the current frame
    page* newPage = (page*) malloc(sizeof(page));
    frame* currentFrame = (frame*) malloc(sizeof(frame));
    // creating the queue
    queue* someQueue = createQueue();
    // variables for writebacks and page faults
    int totalWritebacks = 0;
    int totalPageFaults = 0;
    // the page number of the head of the queue
    int nextInQueue = -1;

    // now moving onto actually simulating checking the frames
    for (i = 0; i < numPages; i++) {

        // get the current page from the queue
        newPage = pageArray[i];

        // get the number of the next page to be replaced
        if (!isEmpty(someQueue)) {
            nextInQueue = someQueue->head->data;
        }

        // get the frame to be updated
        currentFrame = frameArray[getFrameToUpdateFIFO(frameArray, numFrames, newPage->pageNumber, nextInQueue)];

        // if the frame is not empty
        if (currentFrame->currentPage != NULL) {

            // write back to memory if page being rotated out is dirty  
            if (currentFrame->currentPage->dirty == 1) {
                totalWritebacks++;
            }

            // if the page was not already in memory then add a page faultS
            if (currentFrame->currentPage->pageNumber != newPage->pageNumber) {
                totalPageFaults++;
                // if this page was not already in memory then it must be added to the queue
                dequeue(someQueue);
                enqueue(someQueue, newPage->pageNumber);
            }

        }

        // if the frame was empty, add a pagefault and add the page number to the queue
        else {
            totalPageFaults++;
            enqueue(someQueue, newPage->pageNumber);
        }

        // updating the frame with the new page
        currentFrame->currentPage = newPage;
    }

    // memory dealloc
    currentFrame = NULL; newPage = NULL; free(newPage); free(currentFrame);
    free(frameArray); 
    free(currentFrame); 

    // returning number of page faults and writebacks
    int* returnData = (int*) malloc(sizeof(int)*2);
    returnData[0] = totalPageFaults; returnData[1] = totalWritebacks;

    return returnData;
}
