#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <alloca.h>

#include "multi_mutex.h"

int multi_mutex_unlock(pthread_mutex_t **mutexv, int mutexc)
{
    (void) mutexv;
    (void) mutexc;
    return 0;
}

int multi_mutex_trylock(pthread_mutex_t **mutexv, int mutexc)
{
    (void) mutexv;
    (void) mutexc;
    return 0;
}

