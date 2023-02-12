#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 120000

void PrintArray(int* arr, int size) {
	for (int i = 0; i < size; ++i) {
		printf("%d ", arr[i]);
	}
	printf("\n"); 
}

int* InitA(int size) {
	int* arr = calloc(size, sizeof(int));

	srand(time(NULL));
	for (int i = 0; i < size; ++i) {
		arr[i] = rand() % 100;
	}

	return arr;
}

int* InitB(int size) {
	int* arr = calloc(size, sizeof(int));

	srand(time(NULL) + 1);
	for (int i = 0; i < size; ++i) {
		arr[i] = rand() % 100;
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
	int* a = InitA(SIZE);
	int* b = InitB(SIZE);

	long long s = CalcS(a, b, SIZE);
	printf("%lld\n", s);

	free(a);
	free(b);

	return 0;
}
