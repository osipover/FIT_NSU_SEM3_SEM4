#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"
#define SIZE 100000
#define ID 1
#define T1 38.0

int CalcCurrentArraySize(int numProc) {
	if (SIZE % (numProc - 1) == 0) {
		return SIZE;
	}
	else {
		return SIZE + (numProc - 1) - (SIZE % (numProc - 1));
	}
}

void InitArray(int* arr, int curArraySize, int numProc) {
	for (int i = 0; i < curArraySize; ++i) {
		arr[i] = (i < SIZE ? i : 0);
	}
}

long long Mult(int* array1, int sizeArray1, int* array2, int sizeArray2) {
	long long result = 0;
	for (int i = 0; i < sizeArray1; ++i) {
		for (int j = 0; j < sizeArray2; ++j) {
			result += array1[i] * array2[j];
		}
	}
	return result;
}

void PrintResult(long long *s, float totalTime, int numProc) {
	float boost = T1 / totalTime;
	float efficiency = (boost / (float)numProc) * 100;
	printf("S = %lld\n", *s);
	printf("Total time: %f\n", totalTime);
	printf("Sp = %f\n", boost);
	printf("Ep = %f", efficiency);
}

void FreeArrays(int* array1, int* array2) {
	free(array1);
	free(array2);
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

	long long s = 0;
	const int bufferSize = curArraySize / (numProc - 1);

	if (rank == 0) {
		InitArray(array1, curArraySize, numProc);
		InitArray(array2, curArraySize, numProc);

		double startTime, endTime;
		startTime = MPI_Wtime();
		int shift = 0;
		for (int i = 1; i < numProc; ++i) {
			MPI_Send(array1 + shift, bufferSize, MPI_INT, i, ID, MPI_COMM_WORLD);
			MPI_Send(array2, SIZE, MPI_INT, i, ID, MPI_COMM_WORLD);
			shift += bufferSize;
		}
		long long stmp = 0;
		for (int i = 1; i < numProc; ++i) {
			MPI_Recv(&stmp, 1, MPI_LONG_LONG, MPI_ANY_SOURCE, ID, MPI_COMM_WORLD, &status);
			s += stmp;
		}
		endTime = MPI_Wtime();
		
		PrintResult(&s, endTime - startTime, numProc);

	}
	else {
		MPI_Recv(array1, bufferSize, MPI_INT, 0, ID, MPI_COMM_WORLD, &status);
		MPI_Recv(array2, SIZE, MPI_INT, 0, ID, MPI_COMM_WORLD, &status);
		s = Mult(array1, bufferSize, array2, SIZE);
		MPI_Send(&s, 1, MPI_LONG_LONG, 0, ID, MPI_COMM_WORLD);
	}
	FreeArrays(array1, array2);
	MPI_Finalize();
	return 0;
}
