// A segregated storage memory allocator.  Complete the code required in the functions below
// to implement a segregated memory allocator.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "alloc.h"

int max_heap_size = 1024;  // default is a 1K heap (pretty small)

void *heap[4] = {NULL,NULL,NULL,NULL}; // the heap bins for each segregated size 8,16,32,64

unsigned int heap_size = 0; // A variable that keeps track of the how much memory we allocated

// allocate_slab uses the default malloc library to allocate memory
// input: size in bytes of slab to allocate
// return: pointer to slab allocated, NULL if allocation would exceed max_heap_size
void *allocate_slab(unsigned int size) {
    return NULL;
}

// Returns a pointer to a heap block of the appropriate
// size.
// If no such block exists in the free list, this function calls
// allocate_slab to get space NUM_HEAP_BLOCKS blocks of the
// appropriate size and adds them to the free list, then returns
// one of them.
void *my_alloc(unsigned int size) {
    return NULL;
}

void my_free(void *ptr) {
    return;
}