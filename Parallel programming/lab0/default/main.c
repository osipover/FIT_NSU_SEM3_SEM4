#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100000

int* InitArray(int size) {
    int* arr = malloc(size * sizeof(int));
    for (int i = 0; i < size; ++i) {
        arr[i] = i;
    }
    return arr;
}

long long CalcS(int* array1, int* array2, int size) {
    long long s = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            s += array1[i] * array2[j];
        }
    }
    return s;
}

int main() {
    int* array1 = InitArray(SIZE);
    int* array2 = InitArray(SIZE);

    time_t startTime, endTime;
    time(&startTime);
    long long s = CalcS(array1, array2, SIZE);
    time(&endTime);

    printf("S = %lld\n", s);
    printf("Time: %f sec\n", difftime(endTime, startTime));

    free(array1);
    free(array2);

    return 0;
}
