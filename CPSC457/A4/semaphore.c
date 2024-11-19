// gonna design this simply as Dijkstra semaphore
typedef struct {

    // the value for the semaphore
    volatile int value;
} semaphore;

// creation method for the semaphore, simply takes value as an input argument
semaphore* createSemaphore(int v) {
    semaphore* newSem = malloc(sizeof(semaphore));
    newSem->value = v;
    return newSem;
}

// wait method for semaphore
void wait(semaphore* sem) {
    // if the value is less than or equal to zero, force thread to wait
    // afterwards, increment the value downwards
    // figure out how to do so while making use of busy waiting

    // something like this, make sure to test this as part of learning threads
    // in c
    while (sem->value <= 0) {
        asm volatile("nop");
    }

    sem->value--;
}

// signal method for semaphore 
void signal(semaphore* sem) {
    // increment the value upwards
    // allow the thread to proceed
    
    // need to figure out how to create some sort of notify method for the threads
    // attached to this semaphore
    sem->value++;
    // some void notify here
}

// essentially
// entry section
// S.wait()

// exit section
// S.signal