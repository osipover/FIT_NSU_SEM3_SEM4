#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <assert.h>
#include <sys/mman.h>

#define STACK_SIZE 4096
#define HEAP_SIZE  4096

void test_stack() {
    int arr[STACK_SIZE];
    sleep(1);
    test_stack();
}

void test_heap(int count) {
    if (count == 1) return;
  
    int* arr = (int*)malloc(HEAP_SIZE * sizeof(int));
    sleep(1);
    test_heap(--count);
    free(arr);
}

void handler_sigsegv(int sig) {
    printf("SIGSEGV was cathed\n");
    exit(1);
}

void catch_sigsegv(char* map) {
    signal(SIGSEGV, handler_sigsegv);

    *map = 10;      //segmentation fault
    char a = *map;  //segmentation fault  
}

void delete_pages(char* map) {
    char* fourth_page = map + getpagesize() * 3;
    printf("begin:\t%p\n", fourth_page);
    printf("end:\t%p\n", fourth_page + getpagesize() * 3);
    munmap(fourth_page, getpagesize() * 3);
    sleep(10);
}

void test_mmap() {
    char* map = (char*)mmap(NULL, getpagesize() * 10, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    
    sleep(10);

    catch_sigsegv(map);

    delete_pages(map);
}

int main(int argc, char** argv) {
    printf("PID: %d\n", getpid());

    sleep(15);

    test_stack();
    test_heap(50);
    test_mmap();
}
