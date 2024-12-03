// c file to simulate the solution 2 for the readers and writers problem from the notes

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "semaphore.c"
#include <time.h>

#define numReaders 10
#define numWriters 6

#define resourceSize 1
#define readtrySize 1
#define wmutexSize 1
#define rmutexSize 1
#define rentrySize 1

// need to create an argument struct to actually pass those along
typedef struct {
    semaphore* someSem;
    int threadId;
}arg_struct;

// arrays to contain information for turnaround times of the readers and writers
clock_t start, end;
double cpu_time_used;
double readerTimes[numReaders];
double writerTimes[numWriters];

// integer variable to keep track of number of writers and readers that currently have access to crit section
volatile int readers = 0;
volatile int writers = 0; 

// function prototypes
void* writer(arg_struct* args); void* reader(arg_struct* args);

// semaphores for use
semaphore* resource; semaphore* readtry; semaphore* wmutex; semaphore* rmutex; semaphore* rentry;

// initializing all the threads id needed
pthread_t tid[numReaders + numWriters];

// sharedResource
int sharedResource = 0xC0FFEE; // readers just read value directly
int newResource = 0xFACADE; // writers will byte by byte change sharedResource to newResource
int holder = 0x0;
int sharedLength = 6;

int main() {

    int i;

    // initializing all of the semaphores
    resource = createSemaphore(resourceSize);
    readtry = createSemaphore(readtrySize);
    wmutex = createSemaphore(wmutexSize);
    rmutex = createSemaphore(rmutexSize);
    rentry = createSemaphore(rentrySize);

    // creating an args struct
    arg_struct* args;

    // initializing writers
    for (i = 0; i < numWriters; i++) {
        args = (arg_struct*) malloc( sizeof(arg_struct) );
        args->threadId = numReaders + i;
        pthread_create(&tid[numReaders + i], NULL, writer, args);
    }

    // fill out rest of main section here
    // initializing readers
    for (i = 0; i < numReaders; i++) {
        args = (arg_struct*) malloc( sizeof(arg_struct) );
        args->threadId = i;
        pthread_create(&tid[i], NULL, reader, args);
    }

    // joining all of the threads
    for (i = 0; i < numReaders + numWriters; i++) {
        pthread_join(tid[i], NULL);
    }

    // checking the final values of sharedResource
    printf("%x\n", sharedResource);

    // freeing all of the resources
    free(rentry); free(rmutex); free(wmutex); free(readtry); free(resource);

    return 0;
}

void* reader(arg_struct* args) {

    // getting the approximate time when the reader starts
    start = clock();
    readerTimes[args->threadId] = (double) start;

    // entry section
    semaphoreWait(rentry, &tid[args->threadId]); // insert method to get thread id into method, prolly using args struct
    semaphoreWait(readtry, &tid[args->threadId]); 
    semaphoreWait(rmutex, &tid[args->threadId]); 
    readers++;
    if (readers == 1) {
        semaphoreWait(resource, &tid[args->threadId]);
    }
    semaphoreSignal(rmutex);
    semaphoreSignal(readtry);
    semaphoreSignal(rentry);

    // actual test code goes here
    printf("%x\n", sharedResource);

    // exit section
    semaphoreWait(rmutex, &tid[args->threadId]);  // again, find a way to get threadId here
    readers--;
    if (readers == 0) {
        semaphoreSignal(resource);
    }
    semaphoreSignal(rmutex);

    // getting the approximate times when the reader ends
    end = clock();
    readerTimes[args->threadId] = (double) (end - readerTimes[args->threadId]);
    readerTimes[args->threadId] /= CLOCKS_PER_SEC;

    return NULL;
}

void* writer(arg_struct* args) {

    // getting the approximate time when the writer starts
    start = clock();
    writerTimes[args->threadId] = (double) start;

    // entry section
    semaphoreWait(wmutex, &tid[args->threadId]);
    writers++;
    if (writers == 1) {
        semaphoreWait(readtry, &tid[args->threadId]);
    }
    semaphoreSignal(wmutex);
    semaphoreSignal(wmutex);

    // insert test code here
    sharedResource &= ~(0xF << (args->threadId % sharedLength) * 4);
    holder = (0xF << (args->threadId % sharedLength) * 4) & (newResource);
    sharedResource |= holder;
    
    // exit section
    semaphoreSignal(resource);
    writers--;
    if (readers == 0) { // should i change this boolean condition?? ruminate
        semaphoreSignal(readtry);
    }
    semaphoreSignal(wmutex);

    // getting the approximate times when the reader ends
    end = clock();
    writerTimes[args->threadId] = (double) (end - writerTimes[args->threadId]);
    writerTimes[args->threadId] /= CLOCKS_PER_SEC;

    return NULL;
}