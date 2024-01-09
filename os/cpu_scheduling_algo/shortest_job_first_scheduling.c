
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_THREADS 5

typedef struct {
    int id;
    int burst_time;
} ThreadArgs;

void *executeThread(void *arg) {
    ThreadArgs *threadArgs = (ThreadArgs *)arg;
    
    printf("Thread %d is running for %d seconds\n", threadArgs->id, threadArgs->burst_time);
    sleep(threadArgs->burst_time);
    printf("Thread %d completed\n", threadArgs->id);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[MAX_THREADS];
    ThreadArgs threadArgs[MAX_THREADS];

    // Initialize thread data (burst times)
    int burst_times[MAX_THREADS] = {3, 1, 4, 2, 5};

    // Create threads
    for (int i = 0; i < MAX_THREADS; ++i) {
        threadArgs[i].id = i + 1;
        threadArgs[i].burst_time = burst_times[i];
        pthread_create(&threads[i], NULL, executeThread, (void *)&threadArgs[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < MAX_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads completed.\n");

    return 0;
}
