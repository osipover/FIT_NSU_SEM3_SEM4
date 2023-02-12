#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100000

void PrintArray(int* arr, int size) {
    for (int i = 0; i < size; ++i) {
	printf("%d ", arr[i]);
    }
    printf("\n"); 
}

int* InitArray(int size) {
    int* arr = malloc(size * sizeof(int));
    for (int i = 0; i < size; ++i) {
	arr[i] = i;
    }

    return arr;
}

long long CalcS(int* a, int* b, int N) {
    long long s = 0;
    for (int i = 0; i < N; ++i) {
	for (int j = 0; j < N; ++j) {
		s += a[i] * b[j];
	}
    }
    return s;
}

int main() {
    time_t start, end;

    int* a = InitArray(SIZE);
    int* b = InitArray(SIZE);

    time(&start);
    long long s = CalcS(a, b, SIZE);
    time(&end);

    printf("%lld\n", s);
    printf("Time: %f sec\n", difftime(end, start));

    free(a);
    free(b);

    return 0;
}
