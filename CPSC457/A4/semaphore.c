#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "tQueue.c"

// the actual semaphore itself
typedef struct {
    int size;           // a variable for the amount of threads that can access the semaphore at any given time 
    volatile int value; // kept volatile to keep consistent across theads
    threadQueue* queue;
    pthread_mutex_t syncLock; // lock needed to maintain synchronization
    pthread_mutex_t signalLock; // lock to actually use for wait and signal
    struct node* next; // node that represents the process to be signaled
    int debug;

} semaphore;

// semaphore creation method
semaphore* createSemaphore(int size){

    semaphore* newSem = (semaphore*) malloc (sizeof (semaphore) );
    newSem->size = size;
    newSem->value = size;
    newSem->queue = createQueue();
    pthread_mutex_init(&(newSem->syncLock), NULL);
    pthread_mutex_init(&(newSem->signalLock), NULL);  
    newSem->debug = 0;

    return newSem;
}

// due to the implementation of syncLock, only one of wait or signal can function at any given time

void semaphoreWait(semaphore* someSem, pthread_t* someThread) {

    // wait immediately locks the syncLock into place before anything else occurs
    pthread_mutex_lock( &(someSem->syncLock) );

    // if there are too many threads that are currently in the semaphore protected section
    // then place within a threadQueue
    if (someSem->value == 0) { 

        pthread_cond_t newCond = PTHREAD_COND_INITIALIZER; // create a new condition
        enqueue(someSem->queue, someThread, &newCond); // enqueue into the thread queue
        pthread_mutex_unlock( &(someSem->syncLock) ); // unlocking the synchronization lock
        pthread_cond_wait( &newCond, &(someSem->signalLock) ); // making use of a separate lock for the signal to put into wait
        someSem->value--; // decrement the value
    }

    else {
        someSem->value--; // otherwise decrement the value
        pthread_mutex_unlock( &(someSem->syncLock) ); // release the sync lock
    }                                           

    return; 
}

void semaphoreSignal(semaphore* someSem) {

    // lock the sync lock immediately
    pthread_mutex_lock( &(someSem->syncLock) );
    
    // increment the value up
    someSem->value++;

    // get the next value from the queue
    someSem->next = dequeue(someSem->queue);
    usleep(10000); // delay a little to keep everything synced up

    // if there is a thread waiting
    if (someSem->next != NULL) {
        someSem->debug = pthread_cond_signal( someSem->next->cond );  // signal it
        while (someSem->debug != 0) {someSem->debug = pthread_cond_signal( someSem->next->cond ); }
        pthread_mutex_unlock( &(someSem->signalLock) );
    }

    // now unlock synchronization lock
    pthread_mutex_unlock( &(someSem->syncLock) );

    return;
}