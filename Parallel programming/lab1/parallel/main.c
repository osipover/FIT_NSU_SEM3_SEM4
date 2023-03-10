#include "mpi.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define SIZE 5
#define EPSILON 0.0001

typedef struct TProcess {
	int rank;
	double* Ap;
	double* bp;
	double* x0;
	int numLinesOfAp;
	int sizeOfAp;
	int sizeOfBp;
	int offsetInA;
	int offsetInB;
} TProcess;

void InitVectorX0(double* x0, int N) {
	for (int i = 0; i < N; ++i) {
		x0[i] = 1.0;
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
	curProc->x0 = (double*)malloc(SIZE * sizeof(double));
	InitVectorX0(curProc->x0, SIZE);
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
	for (int i = 0; i < N; ++i) {
	for (int j = 0; j < N; ++j) {
		A[i * N + j] = i * N + j + 1;
		}
   }
	//for (int i = 0; i < N; ++i) {
	//	for (int j = 0; j < N; ++j) {
	//		double value = (double)rand()/RAND_MAX + (i == j ? (double)SIZE / 100 : 0);
	//		A[i * N + j] = (i > j ? A[j * N + i] : value);
 //		}
	//}
}

void InitVectorB(double* b, int N) {
	for (int i = 0; i < N; ++i) {
		b[i] =  i + 1;
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

double* InitVectorRp(TProcess* curProc) {
	double* rp = (double*)malloc(curProc->sizeOfBp * sizeof(double));
	double* tmp = (double*)malloc((curProc->sizeOfAp / SIZE) * sizeof(double));
	MatrixMULT(curProc->Ap, curProc->x0, tmp, curProc->numLinesOfAp, SIZE, 1);
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

bool IsSolutionReached(double* rp, double* bp, TProcess* curProc) {
	double fakeNormRp = FakeNorm(rp, curProc->sizeOfBp);
	double fakeNormBp = FakeNorm(bp, curProc->sizeOfBp);

	double fakeNormR = 0.0;
	double fakeNormB = 0.0;

	MPI_Allreduce(&fakeNormRp, &fakeNormR, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
	MPI_Allreduce(&fakeNormBp, &fakeNormB, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

	return (fakeNormR/fakeNormB) < (EPSILON * EPSILON);
}

void CalcNextAlpha(double* alpha, double* rp, double* zp, TProcess* curProc) {
	double dotRp = DotProduct(rp, rp, curProc->sizeOfBp);
	double* tmp = (double*)malloc(curProc->sizeOfBp * sizeof(double));
	MatrixMULT(curProc->Ap, zp, tmp, curProc->numLinesOfAp, SIZE, 1);
	double dotTmp = DotProduct(tmp, zp, curProc->sizeOfBp);

	double dotNomin = 0.0;
	double dotDenom = 0.0;

	MPI_Allreduce(&dotRp, &dotNomin, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
	MPI_Allreduce(&dotTmp, &dotDenom, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

	*alpha = dotNomin / dotDenom;
}


void ConjugateGradientMethod(TProcess* curProc) {
	double* rp = InitVectorRp(curProc);
	double* zp = (double*)malloc(curProc->sizeOfBp * sizeof(double));
	CopyMatrix(rp, zp, curProc->sizeOfBp);

	double alpha = 0.0;
	double beta = 0.0;

	while (!IsSolutionReached(rp, zp, curProc)) {
		CalcNextAlpha(&alpha, rp, zp, curProc);


	}
	//}
}



void FreeMemory(int* numLines, int* offsetLines, double* A, double* x, double* b) {
	free(numLines);
	free(offsetLines);
	free(A);
	free(x);
	free(b);
}

int main(int argc, char** argv) {
	int numProc, rank;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numProc);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int* numLinesA = CalcNumLines(numProc, SIZE, SIZE);
	int* offsetLinesA = CalcOffsetLines(numLinesA, numProc);
	int* numLinesB = CalcNumLines(numProc, SIZE, 1);
	int* offsetLinesB = CalcOffsetLines(numLinesB, numProc);

	PrintVectorInt(numLinesB, numProc);

	double* A = (double*)malloc(SIZE * SIZE * sizeof(double));
	double* b = (double*)malloc(SIZE * sizeof(double));
	double* x = (double*)malloc(SIZE * sizeof(double));
	//double* x0 = (double*)malloc(SIZE * sizeof(double));

	if (rank == 0) {
		InitMatrixA(A, SIZE);
		InitVectorB(b, SIZE);	
		//PrintVectorDouble(A, SIZE * SIZE);
		//PrintVectorDouble(b, SIZE);
	}



	TProcess curProc;
	InitCurProccess(&curProc, rank, numLinesA, numLinesB, offsetLinesA, offsetLinesB);
	//double* Ap = (double*)malloc(numLinesA[rank] * sizeof(double));
	//double* bp = (double*)malloc(numLinesB[rank] * sizeof(double));

	MPI_Scatterv(A, numLinesA, offsetLinesA, MPI_DOUBLE, curProc.Ap, numLinesA[rank], MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Scatterv(b, numLinesB, offsetLinesB, MPI_DOUBLE, curProc.bp, numLinesB[rank], MPI_DOUBLE, 0, MPI_COMM_WORLD);

	//printf("RANK: %d\n", rank);
	//PrintVectorDouble(curProc.Ap, curProc.sizeOfAp);

	ConjugateGradientMethod(&curProc);

	free(numLinesA);
	free(offsetLinesA);
	free(A);
	free(curProc.x0);
	free(b);
	free(curProc.Ap);
}

//C:\Users\osipo\OneDrive\Рабочий стол\NSU\2\ОПП\lab1\Debug

//double A[] = {
//	3, 5.6, 1.9,
//	5.6, 8.9, 4.8,
//	1.9, 4.8, 11.2
//};
//double x[] = { 0.0, 0.0, 0.0 };
//double b[] = { 1, 2, 3 };
