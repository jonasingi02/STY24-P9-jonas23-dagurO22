#define _POSIX_C_SOURCE 199309L
#include "testlib.h"
#include "malloc.h"
#include <omp.h>

#define MAXBLOCK 100

int main()
{
	void *block[MAXBLOCK];

	test_start("malloc.c");
	initAllocator();

	#pragma omp parallel for
	for(int i=0; i<MAXBLOCK; i++) {
		block[i] = my_malloc(42 + (MAXBLOCK-i)*4);
	}

	#pragma omp parallel for
	for(int i=0; i<MAXBLOCK; i++) {
		my_free(block[i]);
	}

	dumpAllocator();

	return test_end();
}
