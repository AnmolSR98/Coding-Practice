#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "semaphore.c"

#define numThreads 30000
#define testSize 1000
// need to create an argument struct to actually pass those along
typedef struct {
    int threadId;
}arg_struct;

// prototype function
void* test(void* args);

// creating the thread ids
pthread_t tid[numThreads];

// num of threads to test at once
semaphore* newSem;

// creating a counter variable to keep track of all the threads
volatile int counter = 0;
volatile int threadsFinished = 0;
volatile int activeThreads = 0;
static int j;

int main() {

    // creating the semaphore to use in this
    newSem = createSemaphore(testSize);

    // creating the struct to pass along args
    arg_struct* args;

    // creating the threads and then starting them using join
    int i;
    for (i = 0; i < numThreads; i++) {
        args = (arg_struct*) malloc( sizeof(arg_struct) );
        args->threadId = i;
        pthread_create(&tid[i], NULL, test, args);
    }
    
    for (i = 0; i < numThreads; i++) {
        pthread_join(tid[i], NULL);
    }

    return 0;
}

// getting freeze error but very rarely

// maybe put the unlock in part of the queue method ????

// very rare now the freeze error

void* test(void* args) {
    arg_struct* actual_args = args;
    
    // insert wait method here
    semaphoreWait(newSem, &tid[actual_args->threadId]);

    sleep(1);

    printf("Thread %d free (total %d)!\n", actual_args->threadId, threadsFinished); // should print all except the last two as there will be no more threads arriving

    // signal here, as the exit section
    semaphoreSignal(newSem);
    threadsFinished++;
    
}