#include "mpi.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <fstream>
#define SIZE 1500
#define EPSILON 0.00001
#define T1 37.0

typedef struct TProcess {
	int rank;
	double* Ap;
	double* bp;
	double* xp;
	int numLinesOfAp;
	int sizeOfAp;
	int sizeOfBp;
	int offsetInA;
	int offsetInB;
} TProcess;

void InitPreSolution(double* x0, int N) {
	for (int i = 0; i < N; ++i) {
		x0[i] = 0.0;
	}
}

void InitCurProccess(TProcess* curProc, int rank, int* numLinesA, int* numLinesB, int* offsetLinesA, int* offsetLinesB) {
	curProc->rank = rank;
	curProc->numLinesOfAp = numLinesA[rank] / SIZE;
	curProc->sizeOfAp = numLinesA[rank];
	curProc->sizeOfBp = numLinesB[rank];
	curProc->offsetInA = offsetLinesA[rank];
	curProc->offsetInB = offsetLinesB[rank];
	curProc->Ap = (double*)malloc(numLinesA[rank] * sizeof(double));
	curProc->bp = (double*)malloc(numLinesB[rank] * sizeof(double));
	curProc->xp = (double*)malloc(numLinesB[rank] * sizeof(double));
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
	//for (int i = 0; i < N; ++i) {
	//	for (int j = 0; j < N; ++j) {
	//		double value = (double)rand() / RAND_MAX + (i == j ? (double)SIZE / 100 : 0);
	//		A[i * N + j] = (i > j ? A[j * N + i] : value);
	//	}
	//}
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

int* CalcNumLines(int numProc, int totalLines, int totalColumns) {
	int* numLines = (int*)malloc(numProc * sizeof(int));
	for (int i = 0; i < numProc; ++i) {
		numLines[i] = totalLines / numProc;
		if (i < totalLines % numProc) ++numLines[i];
		numLines[i] *= totalColumns;
	}
	return numLines;
}
int* CalcOffsetLines(const int* numLines, int numProc) {
	int* offsetLines = (int*)malloc(numProc * sizeof(int));
	int offset = 0;
	for (int i = 0; i < numProc; ++i) {
		offsetLines[i] = offset;
		offset += numLines[i];
	}
	return offsetLines;
}

void CopyMatrix(double* source, double* purpose, int size) {
	for (int i = 0; i < size; ++i) {
		purpose[i] = source[i];
	}
}

void MatrixMULT(double* A, double* B, double* C, int L, int M, int N) {
	for (int i = 0; i < L; ++i) {
		for (int j = 0; j < N; ++j) {
			C[i * N + j] = 0;
			for (int k = 0; k < M; ++k) {
				C[i * N + j] += A[i * M + k] * B[k * N + j];
			}
		}
	}
}

void MatrixSUB(double* A, double* B, double* C, int N) {
	for (int i = 0; i < N; ++i) {
		C[i] = A[i] - B[i];
	}
}

double* InitVectorRp(TProcess* curProc, double* x) {
	double* rp = (double*)malloc(curProc->sizeOfBp * sizeof(double));
	double* tmp = (double*)malloc((curProc->sizeOfAp / SIZE) * sizeof(double));
	MatrixMULT(curProc->Ap, x, tmp, curProc->numLinesOfAp, SIZE, 1);
	MatrixSUB(curProc->bp, tmp, rp, curProc->sizeOfBp);
	free(tmp);
	return rp;
}

double DotProduct(double* a, double* b, int size) {
	double dot = 0.0;
	for (int i = 0; i < size; ++i) {
		dot += (a[i] * b[i]);
	}
	return dot;
}

double FakeNorm(double* vector, int size) {
	double fakeNorm = 0;
	for (int i = 0; i < size; ++i) {
		fakeNorm += (vector[i] * vector[i]);
	}
	return fakeNorm;
}

bool IsSolutionReached(double* rp, TProcess* curProc) {
	double fakeNormRp = FakeNorm(rp, curProc->sizeOfBp);
	static const double fakeNormBp = FakeNorm(curProc->bp, curProc->sizeOfBp);

	double fakeNormR = 0.0;
	double fakeNormB = 0.0;

	MPI_Allreduce(&fakeNormRp, &fakeNormR, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
	MPI_Allreduce(&fakeNormBp, &fakeNormB, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

	return (fakeNormR / fakeNormB) < (EPSILON * EPSILON);
}

void CalcNextAlpha(double* alpha, double* rp, double* z, double* zp, TProcess* curProc) {
	double dotRp = DotProduct(rp, rp, curProc->sizeOfBp);
	double dotNomin = 0.0;
	MPI_Allreduce(&dotRp, &dotNomin, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

	double* tmp = (double*)malloc(curProc->sizeOfBp * sizeof(double));
	MatrixMULT(curProc->Ap, z, tmp, curProc->numLinesOfAp, SIZE, 1);
	double dotTmp = DotProduct(tmp, zp, curProc->sizeOfBp);
	double dotDenom = 0.0;
	MPI_Allreduce(&dotTmp, &dotDenom, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

	*alpha = dotNomin / dotDenom;
	free(tmp);
}

void CalcNextBeta(double* beta, double* rp, double* rp_next, TProcess* curProc) {
	double dotRpNext = DotProduct(rp_next, rp_next, curProc->sizeOfBp);
	double dotRp = DotProduct(rp, rp, curProc->sizeOfBp);

	double dotNomin = 0.0;
	double dotDenom = 0.0;

	MPI_Allreduce(&dotRpNext, &dotNomin, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
	MPI_Allreduce(&dotRp, &dotDenom, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

	*beta = dotNomin / dotDenom;
}

void MatrixADD(double* A, double* B, double* C, int N) {
	for (int i = 0; i < N; ++i) {
		C[i] = A[i] + B[i];
	}
}

void ScalarMULT(double scalar, double* matrix, double* result, int N) {
	for (int i = 0; i < N; ++i) {
		result[i] = scalar * matrix[i];
	}
}

void CalcNextXp(TProcess* curProc, double* zp, double alpha) {
	double* tmp = (double*)malloc(curProc->sizeOfBp * sizeof(double));
	ScalarMULT(alpha, zp, tmp, curProc->sizeOfBp);
	MatrixADD(tmp, curProc->xp, curProc->xp, curProc->sizeOfBp);
	free(tmp);
}

void CalcNextRp(TProcess* curProc, double* rp, double* z, double* zp, double alpha, double* rp_next) {
	double* tmp = (double*)malloc(curProc->sizeOfBp * sizeof(double));
	MatrixMULT(curProc->Ap, z, tmp, curProc->numLinesOfAp, SIZE, 1);
	ScalarMULT(alpha, tmp, tmp, curProc->sizeOfBp);
	MatrixSUB(rp, tmp, rp_next, curProc->sizeOfBp);
	free(tmp);
}

void CalcNextZp(TProcess* curProc, double* zp, double* rp_next, double beta) {
	ScalarMULT(beta, zp, zp, curProc->sizeOfBp);
	MatrixADD(rp_next, zp, zp, curProc->sizeOfBp);
}

void ConjugateGradientMethod(TProcess* curProc, double* x, int* numLinesB, int* offsetLinesB) {
	double* rp = InitVectorRp(curProc, x);
	double* rp_next = (double*)malloc(curProc->sizeOfBp * sizeof(double));
	double* z = (double*)malloc(SIZE * sizeof(double));
	double* zp = (double*)malloc(curProc->sizeOfBp * sizeof(double));

	CopyMatrix(rp, zp, curProc->sizeOfBp);

	double alpha = 0.0;
	double beta = 0.0;

	int count = 0;

	while (!IsSolutionReached(rp, curProc) && (count < 50000)) {
		MPI_Allgatherv(zp, curProc->sizeOfBp, MPI_DOUBLE, z, numLinesB, offsetLinesB, MPI_DOUBLE, MPI_COMM_WORLD);
		CalcNextAlpha(&alpha, rp, z, zp, curProc); 
		CalcNextXp(curProc, zp, alpha); 
		CalcNextRp(curProc, rp, z, zp, alpha, rp_next); 
		CalcNextBeta(&beta, rp, rp_next, curProc); 
		CalcNextZp(curProc, zp, rp_next, beta);
		CopyMatrix(rp_next, rp, curProc->sizeOfBp);
		++count;
	}

	MPI_Gatherv(curProc->xp, curProc->sizeOfBp, MPI_DOUBLE, x, numLinesB, offsetLinesB, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	if (curProc->rank == 0) {
		printf("Number of iterations: %d\n", count);
	}
	//MPI_Allgatherv(curProc->xp, curProc->sizeOfBp, MPI_DOUBLE, x, numLinesB, offsetLinesB, MPI_DOUBLE, MPI_COMM_WORLD);
}


void FreeMemory(double *A, double *b, double *x, int *numLinesA, int *offsetLinesA, int *numLinesB, int *offsetLinesB, TProcess *curProc) {
	free(A);
	free(x);
	free(b);
	free(numLinesA);
	free(offsetLinesA);
	free(numLinesB);
	free(offsetLinesB);
	free(curProc->Ap);
	free(curProc->bp);
	free(curProc->xp);
}

void PrintResult(float totalTime, int numProc) {
	float boost = T1 / totalTime;
	float efficiency = (boost / (float)numProc) * 100;
	printf("Number of processes: %d\n", numProc);
	printf("Total time: %f sec\n", totalTime);
	printf("Sp = %f\n", boost);
	printf("Ep = %f%\n", efficiency);
}

int main(int argc, char** argv) {
	int numProc, rank;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	double startTime = MPI_Wtime();
	MPI_Comm_size(MPI_COMM_WORLD, &numProc);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int* numLinesA = CalcNumLines(numProc, SIZE, SIZE);
	int* offsetLinesA = CalcOffsetLines(numLinesA, numProc);
	int* numLinesB = CalcNumLines(numProc, SIZE, 1);
	int* offsetLinesB = CalcOffsetLines(numLinesB, numProc);

	double* A = (double*)malloc(SIZE * SIZE * sizeof(double));
	double* b = (double*)malloc(SIZE * sizeof(double));
	double* x = (double*)malloc(SIZE * sizeof(double));
	InitPreSolution(x, SIZE);

	if (rank == 0) {
		InitMatrixA(A, SIZE);
		InitVectorB(b, SIZE);
	}

	TProcess curProc;
	InitCurProccess(&curProc, rank, numLinesA, numLinesB, offsetLinesA, offsetLinesB);

	MPI_Scatterv(A, numLinesA, offsetLinesA, MPI_DOUBLE, curProc.Ap, numLinesA[rank], MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Scatterv(b, numLinesB, offsetLinesB, MPI_DOUBLE, curProc.bp, numLinesB[rank], MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Scatterv(x, numLinesB, offsetLinesB, MPI_DOUBLE, curProc.xp, numLinesB[rank], MPI_DOUBLE, 0, MPI_COMM_WORLD);

	ConjugateGradientMethod(&curProc, x, numLinesB, offsetLinesB);
	double endTime = MPI_Wtime();

	if (rank == 0) {
		PrintResult(endTime - startTime, numProc);
	}
	
	FreeMemory(A, b, x, numLinesA, offsetLinesA, numLinesB, offsetLinesB, &curProc);
	MPI_Finalize();

	return 0;
}

//C:\Users\osipo\OneDrive\Рабочий стол\NSU\2\ОПП\lab1\Debug


//double A[] = {
//	3, 5.6, 1.9,
//	5.6, 8.9, 4.8,
//	1.9, 4.8, 11.2
//};
//double x[] = { 0.0, 0.0, 0.0 };
//double b[] = { 1, 2, 3 };
