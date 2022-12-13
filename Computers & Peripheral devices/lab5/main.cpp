#include <cstdlib>
#include <iostream>
#include <stdint.h>
#include <limits.h>
#include <fstream>
#include "matrix.h" 

#define N_MIN 256
#define N_MAX 8388608
#define K 5
#define STEP 1.2
#define ATTEMPTS 5

uint64_t GetTSC() {
	uint64_t highPart, lowPart;
	asm volatile("rdtsc\n":"=a"(lowPart), "=d"(highPart));
	return (highPart << 32) | (lowPart);
}

void PrintArray(int* arr, int size) {
	for (int i = 0; i < size; ++i) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

int* GetDirectElem(int size) {
	int* arr = new int[size];
	arr[size - 1] = 0;
	for (int i = 0; i < size - 1; ++i) {
		arr[i] = i + 1;
	}
	return arr;
}

int* GetBackElem(int size) {
	int* arr = new int[size];
	arr[0] = size - 1;
	for (int i = size - 1; i > 0; --i) {
		arr[i] = i - 1;
	}
	return arr;
}

int FindNext(int cur, int* arr, int size) {
	int next = 0;
	do {
		next = rand() % size;
	} while ((arr[next] != -1) || (next == cur));
	return next;
}

int* GetRandElem(int size) {
	int* arr = new int[size];
	for (int i = 0; i < size; ++i) {
		arr[i] = -1;
	}
	srand(time(NULL));
	int cur = 0, next = 0;
	for (int i = 0; i < size - 1; ++i) {
		next = FindNext(cur, arr, size);
		arr[cur] = next;
		cur = next;
	}
	arr[cur] = 0;

	return arr;
}

void WarmCPU() {
	std::ifstream input;
	input.open("matrix.txt");
	Matrix A(100);
	Matrix B(100);
	A.init(input);
	B.init(input);
	Matrix C = A * B;
}

void WarmCache(int* arr, int size) {
	int k = 0;
	for (int i = 0; i < size * K; ++i) {
		k = arr[k];
	}
	if (k == 12345) std::cout << "Wow!";
}

uint64_t GetTestResults(int* arr, int size) {
	uint64_t start, end;
	uint64_t accessTime = 0, minAccessTime = INT_MAX;

	WarmCPU();
	WarmCache(arr, size);
	
	for (int count = 0; count < ATTEMPTS; ++count){
	    int k = 0;
	    start = GetTSC();
	    for (int i = 0; i < size * K; ++i){
		k = arr[k];
	    }
	    end = GetTSC();
	    if (k == 12345) std::cout << "Wow!";
	    accessTime = (end - start)/(size * K);
	    if (accessTime < minAccessTime) minAccessTime = accessTime;
	}
	delete [] arr;
	return minAccessTime;
}

int main() {
	std::ofstream output;
	output.open("output.csv");
	output << "N;DIRECT;BACK;RANDOM;\n";

	int N = N_MIN;
	while (N <= N_MAX) {
		output << N * sizeof(int) << ";";

		int* arr = GetDirectElem(N);
		output << GetTestResults(arr, N) << ";";
		
		arr = GetBackElem(N);
		output << GetTestResults(arr, N) << ";";

		arr = GetRandElem(N);
		output << GetTestResults(arr, N) << ";\n";

		N *= STEP;
	}
	output.close();
	return 0;
}
