#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

/* Flags to indicate wheather a slot is empty or full */
int empty_slots = BUFFER_SIZE;
int full_slots = 0;

void* producer(void* arg){
    int item = 1;
    while(1){
        /*Busy wait for empty slot */
        while(empty_slots == 0);
        /* produce item and add to the buffer with synchronization */
        buffer[in] = item;
        printf("Producer item %d at index %d\n",buffer[in],in);
        /* using circular queue */
        in = (in + 1) % BUFFER_SIZE;
        item++;

        /* signal that a slot is full */
        full_slots++;
        /* signal that a slot is empty */
        empty_slots--;

        sleep(1);
    }
    pthread_exit(NULL);
}

void* consumer(void* arg){
    int item;
    while(1){
        /* wait for full slot */
        while(full_slots == 0);
        /* consume item and remove from the buffer with synchronization */
        item = buffer[out];
        printf("Consumer item %d at index %d\n",item,out);
        /* using circular queue */
        out = (out + 1) % BUFFER_SIZE;

        /* signal that a slot is empty */
        empty_slots++;
        /* signal that a slot is full */
        full_slots--;

        sleep(2);
    }
    pthread_exit(NULL);
}

int main(){
    pthread_t producer_thread, consumer_thread;

    /* creating producer and consumer thread */
    pthread_create(&producer_thread,NULL,producer,NULL);
    pthread_create(&consumer_thread,NULL,consumer,NULL);

    /* waiting for the threads to terminate */
    pthread_join(producer_thread,NULL);
    pthread_join(consumer_thread,NULL);

    return 0;
}