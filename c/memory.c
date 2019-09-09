
// set in 19XX.ld
#include "memory.h"

void memory_init() {
    // set index of memory heap
    memory_curr = 0;
}

void * memory_allocate(u32 size) {
    // get start address of memory
    void * ret = &memory_heap[memory_curr];

    // increment memory address by size rounded up to 8 (64 bit alignment)
    memory_curr += size;
    while ((u32) memory_curr % 8 != 0) {
        memory_curr += 1;
    }

    return ret;
}

void * memory_copy(void * dest, void * src, u32 size) {
    // copy words 32 bits at a time (lw, sw)
    u32 * destination = dest;
    u32 * source = src;
    u32 i = 0;

    while (size > (sizeof(u32) - 1)) {
        destination[i] = source[i];
        size -= sizeof(u32);
        i++;
    }

    // copy last few bytes (lb, sb)
    u8 * destination_cleanup = (u8 *) &destination[i];
    u8 * source_cleanup = (u8 *) &source[i];
    u8 j = 0;
    while (size != 0) {
        destination_cleanup[j] = source_cleanup[j];
        size -= sizeof(u8);
        j++;
    }
    
    // return original dest
    return dest;
}

// temporary, delete these later
void * malloc(u32 size) {
    return memory_allocate(size);
}

void * memcpy(void * dest, void * src, u32 size) {
    return memory_copy(dest, src, size);
}

