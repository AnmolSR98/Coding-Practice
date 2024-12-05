// c file to simulate the solution 3 for the readers and writers problem from the notes

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "semaphore.c"
#include <time.h> // needed for time measurement
#include "calc.c"

#define mutexSize 1
#define resourceSize 1
#define numWriters 6
#define numReaders 10
#define numCycles 1000

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

// integer variable to keep track of number of readers and writers that currently have access to crit section
volatile int readers = 0;
volatile int writers = 0;

// function prototypes
void* writer(arg_struct* args); void* reader(arg_struct* args);

// semaphores for use
semaphore* mutex; semaphore* resource;

// initializing all the threads id needed
pthread_t tid[numReaders + numWriters];

// sharedResource
int sharedResource = 0xC0FFEE; // readers just read value directly
int newResource = 0xFACADE; // writers will byte by byte change sharedResource to newResource
int holder = 0x0;
int sharedLength = 6;

int main() {

    mutex = createSemaphore(mutexSize);
    resource = createSemaphore(resourceSize);

    // fill out rest of main section here
    // creating an args struct
    arg_struct* args;

    // initializing readers
    int i;
    for (i = 0; i < numReaders; i++) {
        args = (arg_struct*) malloc( sizeof(arg_struct) );
        args->threadId = i;
        pthread_create(&tid[i], NULL, reader, args);
    }

    // initializing writers
    for (i = 0; i < numWriters; i++) {
        args = (arg_struct*) malloc( sizeof(arg_struct) );
        args->threadId = numReaders + i;
        pthread_create(&tid[numReaders + i], NULL, writer, args);
    }

    // joining all of the threads
    for (i = 0; i < numReaders + numWriters; i++) {
        pthread_join(tid[i], NULL);
    }

    // checking the final values of sharedResource
    printf("%x\n", sharedResource);
    printf("%.10f\n", readerTimes[0]);

    // end of cycle print statements
    printf("Readers-Writers Solution 1 (time in seconds)\n");
    printf("Writers | AVG Reader TAT | AVG Writer TAT | AVG TAT\n");
    printf("%2d      | %6.7f | %6.7f | %3.3f\n", numWriters,
        getAverage(readerTimes, numReaders), getAverage(writerTimes, numWriters), 
        ( numReaders * getAverage(readerTimes, numReaders) + numWriters * getAverage(writerTimes, numWriters) ) / (numWriters + numReaders) );


    // freeing all of the resources used

    return 0;
}

void* reader(arg_struct* args) {

    // getting the approximate time when the reader starts
    start = clock();
    readerTimes[args->threadId] = (double) start;

    int i;
    for (i = 0; i < numCycles; i++) {

        // entry section
        semaphoreWait(mutex, &tid[args->threadId]);
        readers++;
        if ((readers == 0) || (writers > 0)) {
            semaphoreSignal(mutex);
            semaphoreWait(resource, &tid[args->threadId]);
            semaphoreWait(mutex, &tid[args->threadId]);
        }
        readers++;
        semaphoreSignal(mutex);

        // actual test code goes here
        printf("%x\n", sharedResource);
        
        // exit section
        semaphoreWait(mutex, NULL);
        readers--;
        if (readers == 0) { // should i change this boolean condition?? ruminate
            semaphoreSignal(resource);
        }
        semaphoreSignal(mutex);

    }

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

    int i;
    for (i = 0; i < numCycles; i++) {

        // entry section
        semaphoreWait(mutex, &tid[args->threadId]); // insert method to get thread id into method, prolly using args struct
        writers++;
        semaphoreSignal(mutex);
        semaphoreWait(resource, &tid[args->threadId]);

        // insert test code here
        sharedResource &= ~(0xF << (args->threadId % sharedLength) * 4);
        holder = (0xF << (args->threadId % sharedLength) * 4) & (newResource);
        sharedResource |= holder;

        // exit section
        semaphoreWait(mutex, &tid[args->threadId]); // again, find a way to get threadId here
        writers--;
        semaphoreSignal(mutex);
        semaphoreSignal(resource);

    }

    // getting the approximate time the writer ends
    end = clock();
    writerTimes[args->threadId] = (double) (end - writerTimes[args->threadId]);
    writerTimes[args->threadId] /= CLOCKS_PER_SEC;


    return NULL;
}