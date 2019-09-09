#include <shorthand.h>
#include <stdlib.h>

void * nalloc(u32 nBytes) {
	return (void *) ((u32) malloc(nBytes) | (u32) 0x80000000);
}