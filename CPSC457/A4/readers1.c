// c file to simulate the solution 1 for the readers and writers problem from the notes
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "semaphore.c"
#include <time.h>
#include "calc.c"

// setting both semaphores to be of size 1
#define mutexSize 1
#define resourceSize 1
// setting the number of cycles
#define numCycles 100

// defining the number of writers and readers
#define numWriters 5
#define numReaders 10

// argument struct to pass through to function
typedef struct {
    semaphore* someSem;
    int threadId;
}arg_struct;

// arrays to contain information for turnaround times of the readers and writers
clock_t start, end;
double cpu_time_used;
double readerTimes[numReaders];
double writerTimes[numWriters];

// integer variable to keep track of number of readers that currently have access to crit section
volatile int readers = 0;

// function prototypes
void* writer(void* args); void* reader(void* args);

// semaphores for use
semaphore* mutex; semaphore* resource;

// initializing all the threads id needed
pthread_t tid[numReaders + numWriters];

// sharedResource variables
int sharedResource = 0xC0FFEE; // readers just read value directly
int newResource = 0xFACADE; // writers will byte by byte change C0FFEE to FACADE
int holder = 0x0;
int sharedLength = 6;

int main() {

    int i;

    // creating the semaphores to use
    mutex = createSemaphore(mutexSize);
    resource = createSemaphore(resourceSize);

    // creating an args struct
    arg_struct* args;

    // initializing readers
    int check = 0;
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
        pthread_join(tid[i], NULL); // getting seg fault on linux for some reason
    }

    // end of cycle print statements
    printf("Readers-Writers Solution 1 (time in seconds)\n");
    printf("Writers | AVG Reader TAT | AVG Writer TAT | AVG TAT\n");
    printf("%2d      | %6.7f | %6.7f | %3.3f\n", numWriters,
        getAverage(readerTimes, numReaders), getAverage(writerTimes, numWriters), 
        ( numReaders * getAverage(readerTimes, numReaders) + numWriters * getAverage(writerTimes, numWriters) ) / (numWriters + numReaders) );


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
        semaphoreWait(mutex, &tid[actual_args->threadId]);
        readers++;
        if (readers == 1) {
            semaphoreWait(resource, &tid[actual_args->threadId]);
        }
        semaphoreSignal(mutex);

        // actual test code goes here
        printf("%x\n", sharedResource);
        
        // exit section
        semaphoreWait(mutex, &tid[actual_args->threadId]);
        readers--;
        if (readers == 0) { 
            semaphoreSignal(resource);
        }
        semaphoreSignal(mutex);

    }

    // getting the approximate times when the reader ends
    end = clock();
    readerTimes[actual_args->threadId] = (double) (end - readerTimes[actual_args->threadId]);
    readerTimes[actual_args->threadId] /= 10000;

    return NULL;

}

void* writer(void* args) {

    arg_struct* actual_args = args;

    // getting the approximate time when the writer starts
    start = clock();
    writerTimes[actual_args->threadId - numReaders] = (double) start;

    int i = 0;
    for (i = 0; i < numCycles; i++) {

        // entry section
        semaphoreWait(resource, &tid[actual_args->threadId]); 
        
        // insert test code here
        sharedResource &= ~(0xF << (actual_args->threadId % sharedLength) * 4);
        holder = (0xF << (actual_args->threadId % sharedLength) * 4) & (newResource);
        sharedResource |= holder;

        // exit section
        semaphoreSignal(resource); 

    }

    // getting the approximate time the writer ends
    end = clock();
    writerTimes[actual_args->threadId - numReaders] = (double) (end - writerTimes[actual_args->threadId - numReaders]);
    writerTimes[actual_args->threadId - numReaders] /= 10000;

    return NULL;
    
}

