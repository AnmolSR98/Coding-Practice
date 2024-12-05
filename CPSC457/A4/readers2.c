// c file to simulate the solution 2 for the readers and writers problem from the notes

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "semaphore.c"
#include <time.h>
#include "calc.c"

#define numReaders 10
#define numWriters 1

#define resourceSize 1
#define readtrySize 1
#define wmutexSize 1
#define rmutexSize 1
#define rentrySize 1
#define numCycles 10

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
void* writer(void* args); void* reader(void* args);

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

    int check = 0;
    // initialzing readers
    for (i = 0; i < numReaders; i++) {
        args = (arg_struct*) malloc( sizeof(arg_struct) );
        args->threadId = i;
        check = pthread_create(&tid[i], NULL, reader, args);
        if (check != 0) {check = pthread_create(&tid[i], NULL, reader, args); }
    }

    // initializing writers
    for (i = numReaders; i < numReaders + numWriters; i++) {
        args = (arg_struct*) malloc( sizeof(arg_struct) );
        args->threadId = i;
        check = pthread_create(&tid[i], NULL, writer, args);
        if (check != 0) {check = pthread_create(&tid[i], NULL, writer, args); }
    }

    // joining all of the threads
    for (i = 0; i < numReaders + numWriters; i++) {
        pthread_join(tid[i], NULL);
    }

    // checking the final values of sharedResource
    printf("%x\n", sharedResource);

    // end of cycle print statements
    printf("Readers-Writers Solution 2 (time in seconds)\n");
    printf("Writers | AVG Reader TAT | AVG Writer TAT | AVG TAT\n");
    printf("%2d      | %6.7f | %6.7f | %3.3f\n", numWriters,
        getAverage(readerTimes, numReaders), getAverage(writerTimes, numWriters), 
        ( numReaders * getAverage(readerTimes, numReaders) + numWriters * getAverage(writerTimes, numWriters) ) / (numWriters + numReaders) );


    // freeing all of the resources

    return 0;
}

void* reader(void* args) {

    arg_struct* actual_args = args;

    // getting the approximate time when the reader starts
    start = clock();
    readerTimes[actual_args->threadId] = (double) start;

    int i;
    for (i = 0; i < numCycles; i++) {

        // entry section
        semaphoreWait(rentry, &tid[actual_args->threadId]); // insert method to get thread id into method, prolly using args struct
        semaphoreWait(readtry, &tid[actual_args->threadId]); 
        semaphoreWait(rmutex, &tid[actual_args->threadId]); 
        readers++;
        if (readers == 1) {
            semaphoreWait(resource, &tid[actual_args->threadId]);
        }
        semaphoreSignal(rmutex);
        semaphoreSignal(readtry);
        semaphoreSignal(rentry);

        // actual test code goes here
        printf("%x\n", sharedResource);

        // exit section
        semaphoreWait(rmutex, &tid[actual_args->threadId]);  // again, find a way to get threadId here
        readers--;
        if (readers == 0) {
            semaphoreSignal(resource);
        }
        semaphoreSignal(rmutex);

    }

    // getting the approximate times when the reader ends
    end = clock();
    readerTimes[actual_args->threadId] = (double) (end - readerTimes[actual_args->threadId]);
    readerTimes[actual_args->threadId] /= CLOCKS_PER_SEC;

    return NULL;
}

void* writer(void* args) {

    arg_struct* actual_args = args;

    // getting the approximate time when the writer starts
    start = clock();
    writerTimes[actual_args->threadId - numReaders] = (double) start;

    int i;
    for (i = 0; i < numCycles; i++) {

        // entry section
        semaphoreWait(wmutex, &tid[actual_args->threadId]);
        writers++;
        if (writers == 1) {
            semaphoreWait(readtry, &tid[actual_args->threadId]);
        }
        semaphoreSignal(wmutex);
        semaphoreWait(resource, &tid[actual_args->threadId]);

        // insert test code here
        sharedResource &= ~(0xF << (actual_args->threadId % sharedLength) * 4);
        holder = (0xF << (actual_args->threadId % sharedLength) * 4) & (newResource);
        sharedResource |= holder;
        
        // exit section
        semaphoreSignal(resource);
        semaphoreWait(wmutex, &tid[actual_args->threadId]);
        writers--;
        if (writers == 0) { // should i change this boolean condition?? ruminate
            semaphoreSignal(readtry);
        }
        semaphoreSignal(wmutex);

    }

    // getting the approximate times when the reader ends
    end = clock();
    writerTimes[actual_args->threadId - numReaders] = (double) (end - writerTimes[actual_args->threadId - numReaders]);
    writerTimes[actual_args->threadId - numReaders] /= CLOCKS_PER_SEC;
    return NULL;
}