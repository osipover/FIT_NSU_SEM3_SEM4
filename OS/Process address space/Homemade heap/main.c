#include "myalloc.h"

int main() {
    init_heap(1024);
    print_heap();

    int* p1 = (int*)mymalloc(5 * sizeof(int));
    print_heap();

    int* p2 = (int*)mymalloc(10 * sizeof(int));
    print_heap();

    myfree(p1);
    print_heap();

    myfree(p2);
    print_heap();
}
