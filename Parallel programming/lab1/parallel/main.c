#include "mpi.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <fstream>
#define SIZE 1200
#define EPSILON 0.00001
#define T1 38.0

void InitPreSolution(double* x0, int N) {
	for (int i = 0; i < N; ++i) {
		x0[i] = 0.0;
	}
}

void PrintMatrix(double* matrix, int size) {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			printf("%f  ", matrix[i * size + j]);
		}
		printf("\n");
	}
	printf("\n");
}

void PrintVectorInt(int* vector, int size) {
	for (int i = 0; i < size; ++i) {
		printf("%d ", vector[i]);
	}
	printf("\n\n");
}

void PrintVectorDouble(double* vector, int size) {
	for (int i = 0; i < size; ++i) {
		printf("%f  ", vector[i]);
	}
	printf("\n\n");
}

void InitMatrixA(double* A, int N) {
	std::ifstream file;
	file.open("A.txt");

	for (int i = 0; i < N * N; ++i) {
		file >> A[i];
	}

	file.close();

	printf("%f\n", A[0]);
	printf("%f\n", A[N * N - 1]);
}

void InitVectorB(double* b, int N) {
	for (int i = 0; i < N; ++i) {
		b[i] = i + 1;
	}
}

void SetMatrixParametrs(int* numLines, int* offsetLines, int numProc, int size) {
	int offset = 0;
	for (int i = 0; i < numProc; ++i) {
		numLines[i] = size / numProc;
		if (i < size / numProc) ++numLines[i];
		numLines[i] *= size;
		offsetLines[i] = offset;
		offset += numLines[i];
	}
}

int* CalcSizesOfAp(int numProc, int totalLines, int totalColumns) {
	int* sizes = (int*)malloc(numProc * sizeof(int));
	for (int i = 0; i < numProc; ++i) {
		sizes[i] = totalLines / numProc;
		if (i < totalLines % numProc) ++sizes[i];
		sizes[i] *= totalColumns;
	}
	return sizes;
}
int* CalcOffsetsOfAp(const int* sizes, int numProc) {
	int* offsets = (int*)malloc(numProc * sizeof(int));
	int offset = 0;
	for (int i = 0; i < numProc; ++i) {
		offsets[i] = offset;
		offset += sizes[i];
	}
	return offsets;
}

void CopyMatrix(double* source, double* purpose, int size, int begin) {
	for (int i = 0; i < size; ++i) {
		purpose[i + begin] = source[i + begin];
	}
}

void MatrixMULT(double* matrix, double* vector, double* result, int M, int N, int begin) {
	for (int i = 0; i < M; ++i) {
		result[i + begin] = 0;
		for (int j = 0; j < N; ++j) {
			result[i + begin] += matrix[i*N + j] * vector[j];
		}
	}
}

void MatrixSUB(double* A, double* B, double* C, int N, int begin) {
	for (int i = 0; i < N; ++i) {
		C[i + begin] = A[i + begin] - B[i + begin];
	}
}

double DotProduct(double* a, double* b, int size, int begin) {
	double dot = 0.0;
	for (int i = 0; i < size; ++i) {
		dot += (a[i + begin] * b[i + begin]);
	}
	return dot;
}

double FakeNorm(double* vector, int size, int begin) {
	double fakeNorm = 0;
	for (int i = begin; i < size + begin; ++i) {
		fakeNorm += (vector[i] * vector[i]);
	}
	return fakeNorm;
}

double CalcFakeNormB(double *b, int *sizes, int *offsets, int rank) {
	static const double fakeNormBp = FakeNorm(b, sizes[rank], offsets[rank]);
	double fakeNormB = 0.0;
	MPI_Allreduce(&fakeNormBp, &fakeNormB, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
	return fakeNormB;
}

bool IsSolutionReached(double *b, double *r, int *sizes, int *offsets, int rank) {
	double fakeNormRp = FakeNorm(r, sizes[rank], offsets[rank]);
	double fakeNormR = 0.0;
	MPI_Allreduce(&fakeNormRp, &fakeNormR, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

	static const double fakeNormB = CalcFakeNormB(b, sizes, offsets, rank);

	return (fakeNormR / fakeNormB) < (EPSILON * EPSILON);
}

void CalcNextAlpha(double* alpha, double *Ap, double* r, double* z, double *dotNomin, int *sizes, int *offsets, int rank, double *tmp) {
	double dotRp = DotProduct(r, r, sizes[rank], offsets[rank]);
	MPI_Allreduce(&dotRp, dotNomin, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

	MatrixMULT(Ap, z, tmp, sizes[rank], SIZE, offsets[rank]);
	double dotTmp = DotProduct(tmp, z, sizes[rank], offsets[rank]);
	double dotDenom = 0.0;
	MPI_Allreduce(&dotTmp, &dotDenom, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

	*alpha = (*dotNomin) / dotDenom;
}

void CalcNextBeta(double* beta, double* r, double *dotR, int *sizes, int *offsets, int rank) {
	double tmp = DotProduct(r, r, sizes[rank], offsets[rank]);
	double dotRnext = 0;
	MPI_Allreduce(&tmp, &dotRnext, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
	*beta = dotRnext / (*dotR);
}

void MatrixADD(double* A, double* B, double* C, int size, int begin) {
	for (int i = 0; i < size; ++i) {
		C[begin + i] = A[begin + i] + B[begin + i];
	}
}

void ScalarMULT(double scalar, double* matrix, double* result, int size, int begin) {
	for (int i = 0; i < size; ++i) {
		result[begin + i] = scalar * matrix[begin + i];
	}
}

void CalcNextXp(double *x, double* z, int *sizes, int *offsets, double alpha, int rank, double *tmp) {
	ScalarMULT(alpha, z, tmp, sizes[rank], offsets[rank]);
	MatrixADD(tmp, x, x, sizes[rank], offsets[rank]);
}

void CalcNextRp(double* r, double* z, double alpha, int *sizes, int *offsets, int rank, double *tmp1, double *tmp2) {
	ScalarMULT(alpha, tmp1, tmp2, sizes[rank], offsets[rank]);
	MatrixSUB(r, tmp2, r, sizes[rank], offsets[rank]);
}

void CalcNextZp(double *z, double *r, double beta, int *sizes, int *offsets, int rank) {
	ScalarMULT(beta, z, z, sizes[rank], offsets[rank]);
	MatrixADD(r, z, z, sizes[rank], offsets[rank]);
}

double* InitVectorR(double *Ap, double *b, double *x, double *tmp, int *sizes, int *offsets, int rank) {
	double* r = (double*)malloc(SIZE * sizeof(double));
	MatrixMULT(Ap, x, tmp, sizes[rank], SIZE, offsets[rank]);
	MatrixSUB(b, tmp, r, sizes[rank], offsets[rank]);
	return r;
}

void ConjugateGradientMethod(double* Ap, double* b, double* x, int* sizes, int* offsets, int rank) {
	double* tmp1 = (double*)malloc(SIZE * sizeof(double));
	double* tmp2 = (double*)malloc(SIZE * sizeof(double));
	double* r = InitVectorR(Ap, b, x, tmp1, sizes, offsets, rank);
	double dotR = 0;

	double* z = (double*)malloc(SIZE * sizeof(double));
	CopyMatrix(r, z, sizes[rank], offsets[rank]);

	MPI_Allgatherv(MPI_IN_PLACE, 0, MPI_DATATYPE_NULL, r, sizes, offsets, MPI_DOUBLE, MPI_COMM_WORLD);
	MPI_Allgatherv(MPI_IN_PLACE, 0, MPI_DATATYPE_NULL, z, sizes, offsets, MPI_DOUBLE, MPI_COMM_WORLD);

	double alpha = 0.0;
	double beta = 0.0;

	int count = 0;

	while (!IsSolutionReached(b, r, sizes, offsets, rank) && (count < 50000)) {
		CalcNextAlpha(&alpha, Ap, r, z, &dotR, sizes, offsets, rank, tmp1); 
		CalcNextXp(x, z, sizes, offsets, alpha, rank, tmp2); 
		CalcNextRp(r, z, alpha, sizes, offsets, rank, tmp1, tmp2);
		CalcNextBeta(&beta, r, &dotR, sizes, offsets, rank); 
		CalcNextZp(z, r, beta, sizes, offsets, rank);
		MPI_Allgatherv(MPI_IN_PLACE, 0, MPI_DATATYPE_NULL, z, sizes, offsets, MPI_DOUBLE, MPI_COMM_WORLD);
		++count;
	}

	MPI_Allgatherv(MPI_IN_PLACE, 0, MPI_DATATYPE_NULL, x, sizes, offsets, MPI_DOUBLE, MPI_COMM_WORLD);
	if (rank == 0) {
		printf("Number of iterations: %d\n", count);
	}
	free(tmp1);
	free(tmp2);
}


void FreeMemory(double *A, double *b, double *x, double *Ap, int *sizes, int *offsets) {
	free(A);
	free(b);
	free(x);
	free(Ap);
	free(sizes);
	free(offsets);
}

void PrintResult(float totalTime, int numProc) {
	float boost = T1 / totalTime;
	float efficiency = (boost / (float)numProc) * 100;
	printf("Number of processes: %d\n", numProc);
	printf("Total time: %f sec\n", totalTime);
	printf("Sp = %f\n", boost);
	printf("Ep = %f\n\n", efficiency);
}

int main(int argc, char** argv) {
	int numProc, rank;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	double startTime = MPI_Wtime();
	MPI_Comm_size(MPI_COMM_WORLD, &numProc);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int* sizes = CalcSizesOfAp(numProc, SIZE, SIZE);
	int* offsets = CalcOffsetsOfAp(sizes, numProc);

	double* A = (double*)malloc(SIZE * SIZE * sizeof(double));
	double* b = (double*)malloc(SIZE * sizeof(double));
	double* x = (double*)malloc(SIZE * sizeof(double));
	InitPreSolution(x, SIZE);

	if (rank == 0) {
		InitMatrixA(A, SIZE);
		InitVectorB(b, SIZE);
	}

	double* Ap = (double*)malloc(sizes[rank] * sizeof(double));

	MPI_Scatterv(A, sizes, offsets, MPI_DOUBLE, Ap, sizes[rank], MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Bcast(b, SIZE, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	for (int i = 0; i < numProc; ++i) {
		sizes[i] /= SIZE;
		offsets[i] /= SIZE;
	}

	ConjugateGradientMethod(Ap, b, x, sizes, offsets, rank);
	double endTime = MPI_Wtime();


	if (rank == 0) {
		PrintResult(endTime - startTime, numProc);
	}
	
	FreeMemory(A, b, x, Ap, sizes, offsets);
	MPI_Finalize();

	return 0;
}
