# pragma once

#include <stdatomic.h>

typedef struct {
    atomic_int count;
} semaphore;

void sem_init(semaphore *s, int value);
void sem_wait(semaphore *s);
void sem_signal(semaphore *s);
