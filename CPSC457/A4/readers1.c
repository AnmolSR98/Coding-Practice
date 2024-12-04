// c file to simulate the solution 1 for the readers and writers problem from the notes
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "semaphore.c"
#include <time.h>

// NEED TO MODIFY TO RUN FOR A 1000 TIMES EACH
// numReaders can be fixed at 10
// MODIFY THE AMOUNT OF numWriters for experimental data

#define mutexSize 1
#define resourceSize 1
#define numWriters 1
#define numReaders 10

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

// integer variable to keep track of number of readers that currently have access to crit section
volatile int readers = 0;

// function prototypes
void* writer(void* args); void* reader(void* args);

// semaphores for use
semaphore* mutex; semaphore* resource;

// initializing all the threads id needed
pthread_t tid[numReaders + numWriters];

// sharedResource
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

    // fill out rest of main section here
    // initializing readers
    for (i = 0; i < numReaders; i++) {
        args = (arg_struct*) malloc( sizeof(arg_struct) );
        args->threadId = i;
        pthread_create(&tid[i], NULL, reader, args);
    }

    // initializing writers
    for (i = numWriters; i < numReaders + numWriters; i++) {
        args = (arg_struct*) malloc( sizeof(arg_struct) );
        args->threadId = i;
        pthread_create(&tid[i], NULL, writer, args);
    }

    // joining all of the threads
    for (i = 0; i < (numReaders + numWriters); i++) {
        pthread_join(tid[i], NULL);
    }

    printf("%x\n", sharedResource);

    // end of cycle print statements
    printf("Readers-Writers Solution 1 (time in seconds)\n");
    printf("Writers | AVG Reader TAT | AVG Writer TAT | AVG TAT\n");
    printf("%2d      | %6.7f | %6.7f | %3.3f\n", 10, 500000.0, 500000.0, 500.0);

    // freeing all of the stuff used
    //free(args); free(mutex); free(resource);


    return 0;
}

void* reader(void* args) {

    arg_struct* actual_args = args;

    // getting the approximate time when the reader starts
    start = clock();
    readerTimes[actual_args->threadId] = (double) start;

    //int i;
    //for (i = 0; i < 1000; i++) {

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

    //}

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
    writerTimes[actual_args->threadId] = (double) start;

    //int i = 0;
    //for (i = 0; i < 1000; i++) {

        //sleep(1); // needed to ensure readers get in before writers

        // entry section
        semaphoreWait(resource, &tid[actual_args->threadId]); // insert method to get thread id into method, prolly using args struct
        
        // insert test code here
        sharedResource &= ~(0xF << (actual_args->threadId % sharedLength) * 4);
        holder = (0xF << (actual_args->threadId % sharedLength) * 4) & (newResource);
        sharedResource |= holder;

        // exit section
        semaphoreSignal(resource); // again, find a way to get threadId here

    //}

    // getting the approximate time the writer ends
    end = clock();
    writerTimes[actual_args->threadId] = (double) (end - writerTimes[actual_args->threadId]);
    writerTimes[actual_args->threadId] /= CLOCKS_PER_SEC;

    return NULL;
    
}

