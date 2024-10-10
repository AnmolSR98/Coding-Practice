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

    // pointers for the next page in the sequence
    page* newPage = (page*) malloc(sizeof(page));
    frame* currentFrame = (frame*) malloc(sizeof(frame));
    // values to keep track of write backs and page faults
    int totalWritebacks = 0;
    int totalPageFaults = 0;

    // now moving onto actually simulating checking the frames
    for (i = 0; i < numPages; i++) {

        // get the current page from the queue
        newPage = pageArray[i];

        // get the frame
        currentFrame = frameArray[getFrameToUpdateOptimal(frameArray, pageArray, numFrames, numPages, newPage->pageNumber, i)];

        // writing back to memory if current page is dirty 
        if (currentFrame->currentPage != NULL) {
            if (currentFrame->currentPage->dirty == 1) {
                totalWritebacks++;
            }
        }
        
        // checking to see if the page number of this frame is different to the page being shifted in, if not, page fault
        if(currentFrame->currentPage!= NULL) {
            if (currentFrame->currentPage->pageNumber != newPage->pageNumber) {
                totalPageFaults++;
            }
        }

        // if the frame was empty, page fault
        else {
            totalPageFaults++;
        }

        // updating the frame with the new page
        currentFrame->currentPage = newPage;

        // calculate the next time this page will appear
        currentFrame->nextArrival = indexOfNextInstance(pageArray, i, numPages, currentFrame->currentPage->pageNumber);
    }

    // dealloc
    currentFrame = NULL; newPage = NULL; free(newPage); free(currentFrame);
    free(frameArray); free(currentFrame);

    // returning data
    int* returnData = (int*) malloc(sizeof(int)*2);
    returnData[0] = totalPageFaults; returnData[1] = totalWritebacks;

    return returnData;
}
