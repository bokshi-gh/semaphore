#include "semaphore.h"
#include <stdio.h>
#include <pthread.h>


semaphore sem;
int counter = 0;

void* thread_func(void* arg) {
    for (int i = 0; i < 100000; i++) {
        sem_wait(&sem);   // take permit
        counter++;        // critical section
        sem_signal(&sem);   // release permit
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    sem_init(&sem, 1);   // binary semaphore → acts like mutex

    pthread_create(&t1, NULL, thread_func, NULL);
    pthread_create(&t2, NULL, thread_func, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final Counter: %d\n", counter);
    return 0;
}
