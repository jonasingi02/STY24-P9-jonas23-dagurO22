#define _POSIX_C_SOURCE 199309L
#include "testlib.h"
#include "multi_mutex.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <omp.h>
#include <time.h>

typedef struct {
    pthread_mutex_t mutex;
    int value;
} MutexAndInt;

#define PUSH_TIMES 10000
#define VALUES 5
#define INITIAL_VALUE 100000

// This makes using nanosleep a bit more convenient.
static inline void usleep(unsigned int time)
{
    struct timespec waitTime = {time / 1000000, (time % 1000000) * 1000};

    nanosleep(&waitTime, NULL);
}

static void tryPushAround(MutexAndInt *from, MutexAndInt *to)
{
    pthread_mutex_t *mutexv[2] = {&from->mutex, &to->mutex};

    for (int i = 0; i < PUSH_TIMES; i++) {
        if (multi_mutex_trylock(mutexv, 2) != 0) {
            continue;
        }
        int f = from->value;
        int t = to->value;
        // random from 1 to 10.
        int transfer = rand() % 10 + 1;
        // Make race conditions a bit more common.
        usleep(1);
        from->value = f - transfer;
        to->value = t + transfer;

        multi_mutex_unlock(mutexv, 2);
    }
}

static int printMutexAndInt(MutexAndInt *values, int count)
{
    printf("Values: ");
    int sum = 0;
    for (int i = 0; i < count; i++) {
        int value = values[i].value;
        printf(" %-7d", value);
        sum += value;
    }
    printf(" (sum: %d)\n", sum);
    return sum;
}

int main()
{
    test_start("multi_mutex.c");

    MutexAndInt values[VALUES];
    for (int i = 0; i < VALUES; i++) {
        if (pthread_mutex_init(&values[i].mutex, NULL) != 0) {
            perror("mutex_init");
            return 1;
        }
        values[i].value = INITIAL_VALUE;
    }

    printMutexAndInt(values, VALUES);
    omp_set_dynamic(0);
    omp_set_num_threads(VALUES);

    #pragma omp parallel for
    for (int i = 0; i < VALUES; i++) {
        tryPushAround(&values[i], &values[(i+1) % VALUES]);
    }

    test_equals_int(printMutexAndInt(values, VALUES), INITIAL_VALUE * VALUES);

    return test_end();
}
