#include "myalloc.h"
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

typedef struct node {    
    size_t size;
    struct node *next;
    struct node *prev;
    bool is_free;
} Node;

typedef struct heap {
    Node *start;
    Node *end;
    size_t size;
} Heap;

Heap heap;

void init_heap(size_t heap_size) {
    heap.size = (heap_size + sizeof(Node) - 1) / sizeof(Node) + 2;
    heap.start = (Node*)mmap(NULL, heap.size * sizeof(Node), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    heap.end = heap.start + heap.size - 1;
    
    heap.start->size = heap.size - 1;
    heap.start->next = heap.end;
    heap.start->prev = NULL; 
    heap.start->is_free = true;

    heap.end->size = 0;
    heap.end->next = NULL;
    heap.end->prev = heap.start;
    heap.end->is_free = false;
}

void *mymalloc(size_t nbytes) {
    Node* current = heap.start;

    size_t nunits = (nbytes + sizeof(Node) - 1) / sizeof(Node) + 1;

    while (current != NULL) {
        if (current->is_free) {
            if (current->size >= nunits) {
                if (current->size > nunits) {
                    Node* tmp = current;
                    current->size -= nunits;
                    current += current->size;

                    current->size = nunits;
                    current->next = tmp->next;
                    current->prev = tmp;

                    tmp->next = current;
                    current->next->prev = current;
                }
                current->is_free = false;
                return (void*)(current + 1);
            }
        }
        current = current->next;
    } 

    return NULL;
}

bool is_pointer_correct(Node* node) {
    if (node->next == NULL) return false;
    if (node->next->prev == NULL) return false;
    if (node != node->next->prev) return false;
    return true;
}

void myfree(void* ptr) {
    if (ptr == NULL) {
        fprintf(stderr, "myfree(): null pointer\n");
        raise(SIGABRT);
    }
    Node* node = (Node*)ptr - 1;
    if (!is_pointer_correct(node)) {
        fprintf(stderr, "myfree(): invalid pointer\n");
        raise(SIGABRT);
    }

    node->is_free = true;
}

void print_heap() {
    int i = 0;
    for (Node* cur = heap.start; cur != NULL; cur = cur->next, ++i) {
        printf("----------- BLOCK %d ----------\n", i);
        printf("addr:\t%p\n", cur);
        printf("next\t%p\n", cur->next);
        printf("prev\t%p\n", cur->prev);
        printf("size\t%ld\n", cur->size);
        printf("free\t%d\n", (int)cur->is_free);
    }        
    printf("-------------------------------\n");
    printf("\n\n");
}
