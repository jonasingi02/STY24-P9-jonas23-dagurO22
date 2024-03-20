#ifndef MULTI_MUTEX_H
#define MULTI_MUTEX_H

#include <pthread.h>

int multi_mutex_unlock(pthread_mutex_t **mutexv, int mutexc);
int multi_mutex_lock(pthread_mutex_t **mutexv, int mutexc);
int multi_mutex_trylock(pthread_mutex_t **mutexv, int mutexc);

#endif

