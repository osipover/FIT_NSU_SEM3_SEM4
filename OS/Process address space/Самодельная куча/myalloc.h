#include <stdio.h>

void init_heap(size_t heap_size);
void *mymalloc(size_t nbytes);
void myfree(void* ptr);
void print_heap();
