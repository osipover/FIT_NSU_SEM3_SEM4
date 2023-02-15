#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"
#define SIZE 100000
#define ID 1
#define T1 38.0

int CalcCurrentArraySize(int numProc) {
	if (SIZE % (numProc) == 0)
		return SIZE;
	else
		return SIZE + (numProc)-(SIZE % (numProc));
}

void InitArray(int* arr, int curArraySize) {
	for (int i = 0; i < curArraySize; ++i) {
		arr[i] = (i < SIZE ? i : 0);
	}
}

long long Mult(int* a, int sizeA, int* b, int sizeB) {
	long long result = 0;
	for (int i = 0; i < sizeA; ++i) {
		for (int j = 0; j < sizeB; ++j) {
			result += a[i] * b[j];
		}
	}
	return result;
}

void PrintResult(long long* s, float totalTime, int numProc) {
	float boost = T1 / totalTime;
	float efficiency = (boost / (float)numProc) * 100;
	printf("S = %lld\n", *s);
	printf("Total time: %f sec\n", totalTime);
	printf("Sp = %f\n", boost);
	printf("Ep = %f%\n", efficiency);
}

void FreeArrays(int* array1, int* array2, int* recvBuffer) {
	free(array1);
	free(array2);
	free(recvBuffer);
}

int main(int argc, char** argv) {
	int numProc, rank;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numProc);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	const int curArraySize = CalcCurrentArraySize(numProc);
	int* array1 = malloc(curArraySize * sizeof(int));
	int* array2 = malloc(curArraySize * sizeof(int));

	const int bufferSize = curArraySize / (numProc);
	int* recvBuffer = malloc(bufferSize * sizeof(int));

	double timeStart, timeEnd;
	if (rank == 0) {
		InitArray(array1, curArraySize);
		InitArray(array2, curArraySize);
		timeStart = MPI_Wtime();
	}
	long long s = 0, stmp = 0;

	MPI_Scatter(array1, bufferSize, MPI_INT, recvBuffer, bufferSize, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(array2, SIZE, MPI_INT, 0, MPI_COMM_WORLD);
	stmp = Mult(recvBuffer, bufferSize, array2, SIZE);
	MPI_Reduce(&stmp, &s, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

	if (rank == 0) {
		timeEnd = MPI_Wtime();
		PrintResult(&s, timeEnd - timeStart, numProc);
	}
	FreeArrays(array1, array2, recvBuffer);
	MPI_Finalize();

	return 0;
}
