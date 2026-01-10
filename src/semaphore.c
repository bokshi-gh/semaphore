#include "semaphore.h"

void sem_init(semaphore *s, int value) {
    atomic_store(&s->count, value);
}

void sem_wait(semaphore *s) {
    int expected;
    
    for (;;) {
        expected = atomic_load(&s->count);
        
        if (expected > 0 && atomic_compare_exchange_strong(&s->count, &expected, expected - 1)) {
            return;
        }
    }
}

void sem_signal(semaphore *s) {
    atomic_fetch_add(&s->count, 1);
}
