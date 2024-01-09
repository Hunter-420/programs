/*

pseudocode
-------------

Producer--
    sem_wait(&empty_slots);
    pthread_mutex_lock(&mutex);
    buffer item // critical section
    pthread_mutex_unlock(&mutex);
    sem_post(&full_slots);

Consumer--
    sem_wait(&full_slots);
    pthread_mutex_lock(&mutex);
    // critical section
    pthread_mutex_unlock(&mutex);
    sem_post(&empty_slots);


*/