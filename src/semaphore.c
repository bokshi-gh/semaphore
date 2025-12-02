#include "semaphore.h"

void sem_init(semaphore *s, int value) {
    atomic_store(&s->count, value);
}

void sem_wait(semaphore *s) {
    int expected;
    while (1) {
        expected = atomic_load(&s->count);
        if (expected > 0) {
            if (atomic_compare_exchange_strong(&s->count, &expected, expected - 1)) {
                break;
            }
        }
    }
}

void sem_signal(semaphore *s) {
    atomic_fetch_add(&s->count, 1);
}

