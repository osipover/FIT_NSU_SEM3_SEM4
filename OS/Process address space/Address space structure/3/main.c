#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define SIZE 100

void test_heap() {
    char* buffer = (char*)malloc(SIZE * sizeof(char));
    strcpy(buffer, "hello world");
    printf("%s\n", buffer);
    free(buffer);

    buffer = (char*)malloc(SIZE * sizeof(char));
    strcpy(buffer, "hello world");
    printf("%s\n", buffer);

    buffer += (SIZE / 2);
  
    /* free(): invalid pointer
     * Аварийный останов
    */
    free(buffer);       
    printf("%s\n", buffer);
}

int main() {
    test_heap();
}
