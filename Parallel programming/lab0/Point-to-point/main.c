#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"
#define SIZE 100000
#define ID 1

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

long long Mult(int* a, int sizeA, int* b, int sizeB) {
	long long result = 0;
	for (int i = 0; i < sizeA; ++i) {
		for (int j = 0; j < sizeB; ++j) {
			result += a[i] * b[j];
		}
	}
	return result;
}

int main(int argc, char** argv) {
	int numProc, rank;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numProc);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	const int curArraySize = CalcCurrentArraySize(numProc);
	int *array1 = malloc(curArraySize * sizeof(int));
	int *array2 = malloc(curArraySize * sizeof(int));

	long long s = 0;
	const int bufferSize = curArraySize / (numProc - 1);

	if (rank == 0) {
		InitArray(array1, curArraySize, numProc);
		InitArray(array2, curArraySize, numProc);

		int shift = 0;
		long long sBuffer = 0;

		double start, end;
		start = MPI_Wtime();
		for (int i = 1; i < numProc; ++i) {
			MPI_Send(array1 + shift, bufferSize, MPI_INT, i, ID, MPI_COMM_WORLD);
			MPI_Send(array2, SIZE, MPI_INT, i, ID, MPI_COMM_WORLD);
			shift += bufferSize;
		}

		for (int i = 1; i < numProc; ++i) {
			MPI_Recv(&sBuffer, 1, MPI_LONG_LONG, MPI_ANY_SOURCE, ID, MPI_COMM_WORLD, &status);
			s += sBuffer;
		}
		end = MPI_Wtime();

		printf("S from parallels realisation: %lld\n", s);
		printf("Total time: %f\n", end - start);
	}
	else {
		MPI_Recv(array1, bufferSize, MPI_INT, 0, ID, MPI_COMM_WORLD, &status);
		MPI_Recv(array2,	SIZE, MPI_INT, 0, ID, MPI_COMM_WORLD, &status);
		s = Mult(array1, bufferSize, array2, SIZE);
		MPI_Send(&s, 1, MPI_LONG_LONG, 0, ID, MPI_COMM_WORLD);
	}

	free(array1);
	free(array2);

	MPI_Finalize();
	
	return 0;
}
