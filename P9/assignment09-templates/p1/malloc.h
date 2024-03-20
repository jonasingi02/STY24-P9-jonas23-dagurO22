#ifndef MALLOC_H
#define MALLOC_H
#include <inttypes.h>

#define ALLOCATED_BLOCK_MAGIC (0xfeedcafecafe)

typedef struct _Block {
	/* The size of this block, including the header
	 * Always a multiple of 8 bytes.
	 */
	uint64_t size;

	/* For a free block: a pointer to the next free block (or NULL for the last block)
	 * For an allocated block: a magic number (ALLOCATED_BLOCK_MAGIC)
	 */
	union {
		struct _Block *next;
		intptr_t magic;
	};

	/* The data area of this block.
	 * (usually application data; in case of a free block, this part is unused)
	 */
	uint8_t data[];
} Block;


#define HEADER_SIZE sizeof(Block)

#define INV_HEADER_SIZE_MASK ~((uint64_t)HEADER_SIZE - 1)

/*
 * This is the heap you should use.
 * 32 MiB heap space per default. The heap does not grow.
 */
#define HEAP_SIZE (32 * 1024 * 1024)


void initAllocator();
void dumpAllocator();

uint64_t roundUp(uint64_t n);
void *my_malloc(uint64_t size);
void my_free(void *address);

#endif

