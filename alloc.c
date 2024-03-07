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
    heap_size += size;
    if (heap_size > max_heap_size) {
        //free(ptr);
        return NULL;
    }
    void *ptr = malloc(size);
    if (ptr == NULL) {
        return NULL;
    }
    
    return ptr;
}

// Returns a pointer to a heap block of the appropriate
// size.
// If no such block exists in the free list, this function calls
// allocate_slab to get space NUM_HEAP_BLOCKS blocks of the
// appropriate size and adds them to the free list, then returns
// one of them.
void *my_alloc(unsigned int size) {
    int bin;
    if (size <= 8) {
        bin = 0;
    } else if (size <= 16) {
        bin = 1;
    } else if (size <= 32) {
        bin = 2;
    } else if (size <= 64) {
        bin = 3;
    } else {
        // Invalid block size
        return NULL;
    }
        if (heap[bin] == NULL){
        unsigned int slab_size = (size + sizeof(blk_header_t)) * NUM_HEAP_BLOCKS;
        
        if (heap_size +slab_size> max_heap_size) {
            printf("Malloc failed, out of memory!\n");
            exit(0);
        }
        void *slab = allocate_slab(slab_size);
        if (slab == NULL) {
            printf("Malloc failed, out of memory!\n");
            exit(0);
        }
        for (int i = 0; i < NUM_HEAP_BLOCKS; i++) {
            blk_header_t *header = slab;
            header->size = size;
            my_free((void *)(header + 1));
            slab = slab + size + sizeof(blk_header_t);
        }
    }
        
        blk_header_t *header = heap[bin];
        heap[bin] = header->next;
        return (void *)(1 + header);

    return NULL; // Return NULL if header is NULL
}


void my_free(void *ptr) {
    // Get the block header
    blk_header_t *header = (blk_header_t *)ptr - 1;
    
    // Check if header is null
    if (header == NULL) {
        // Invalid pointer
        return;
    }
    
    // Check if header is null before accessing its size field
    if (header != NULL) {
        // Determine the bin based on the block size
        int bin;
        if (header->size <= 8) {
            bin = 0;
        } else if (header->size <= 16) {
            bin = 1;
        } else if (header->size <= 32) {
            bin = 2;
        } else if (header->size <= 64) {
            bin = 3;
        } else {
            // Invalid block size
            return;
        }
        
        // Add the block to the free list
        blk_header_t *blk = heap[bin];
        header->next = blk;
        heap[bin] = header;
}
}
