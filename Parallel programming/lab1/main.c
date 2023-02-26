#include "mpi.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cmath>
#define SIZE 1000
#define EPSILON 0.0001

void PrintVector(double* vector, int N) {
	for (int i = 0; i < N; ++i) {
		std::cout << vector[i] << " ";
	}
	std::cout << std::endl;
}

double* InitPreSolution(int N) {
	double* vector = (double*)malloc(N * sizeof(double));
	for (int i = 0; i < N; ++i) {
		vector[i] = 0.0;
	}
	return vector;
}

void CopyMatrix(double* source, double* purpose, int size) {
	for (int i = 0; i < size; ++i) {
		purpose[i] = source[i];
	}

}

void MatrixMULT(double* A, double* B, double* C, int L, int M, int N) {
	for (int i = 0; i < L; ++i) {
		for (int j = 0; j < N; ++j) {
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

double* InitVectorR(double* A, double* x, double* b) {
	double* r = (double*)calloc(SIZE, sizeof(double));
	double* tmp = (double*)calloc(SIZE, sizeof(double));
	MatrixMULT(A, x, tmp, SIZE, SIZE, 1);
	MatrixSUB(b, tmp, r, SIZE);
	free(tmp);
	return r;
}

double DotProduct(double* a, double* b) {
	double dot = 0.0;
	for (int i = 0; i < SIZE; ++i) {
		dot += a[i] * b[i];
	}
	return dot;
}

double Norm(double* vector) {
	double norm = 0.0;
	for (int i = 0; i < SIZE; ++i) {
		norm += (vector[i] * vector[i]);
	}
	return std::sqrt(norm);
}

bool isSolutionReached(double* r, double* b) {
	return (Norm(r) / Norm(b)) < EPSILON;
}

double CalcNextAlpha(double* A, double* r, double* z) {
	double* tmp = (double*)calloc(SIZE, sizeof(double));
	MatrixMULT(A, z, tmp, SIZE, SIZE, 1);
	double alpha = DotProduct(r, r) / DotProduct(tmp, z);
	free(tmp);
	return alpha;
}

double CalcNextBeta(double* r_next, double* r) {
	return DotProduct(r_next, r_next) / DotProduct(r, r);
}

void ScalarMULT(double scalar, double* matrix, double* result, int N) {
	for (int i = 0; i < N; ++i) {
		result[i] = scalar * matrix[i];
	}
}

void MatrixADD(double* A, double* B, double* C, int N) {
	for (int i = 0; i < N; ++i) {
		C[i] = A[i] + B[i];
	}
}

void CalcNextX(double* x, double* z, double alpha) {
	double* tmp = (double*)calloc(SIZE, sizeof(double));
	ScalarMULT(alpha, z, tmp, SIZE);
	MatrixADD(x, tmp, x, SIZE); 
	free(tmp);
}

void CalcNextR(double* A, double* r, double* z, double alpha, double* r_next) {
	double* tmp = (double*)calloc(SIZE, sizeof(double));
	MatrixMULT(A, z, tmp, SIZE, SIZE, 1);
	ScalarMULT(alpha, tmp, tmp, SIZE);
	MatrixSUB(r, tmp, r_next, SIZE); 
	free(tmp);
}

void CalcNextZ(double beta, double* r_next, double* z) {
	ScalarMULT(beta, z, z , SIZE);
	MatrixADD(r_next, z, z, SIZE);
}

void ConjugateGradientMethod(double* A, double* x, double* b) {
	double* r = InitVectorR(A, x, b);
	double* r_next = (double*)malloc(SIZE * sizeof(double));
	double* z = (double*)malloc(SIZE * sizeof(double));
	CopyMatrix(r, z, SIZE);

	double alpha = 0.0;
	double beta = 0.0;

	int count = 0;

	while (!isSolutionReached(r, b) && (count < 50000)) {
		alpha = CalcNextAlpha(A, r, z);
		CalcNextX(x, z, alpha);
		CalcNextR(A, r, z, alpha, r_next);
		beta = CalcNextBeta(r_next, r);
		CalcNextZ(beta, r_next, z);
		CopyMatrix(r_next, r, SIZE);
		++count;
	}
	std::cout << count << std::endl << std::endl;
}

double* InitMatrixA(int N) {
	double* A = (double*)malloc(N * N * sizeof(double));

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			A[i * N + j] = i * N + j;
			//double value = (double)rand() / double(RAND_MAX);
			//if (rand() % 2 == 0) value *= -1.0;
			//if (i == j) value += N;
			//A[i*N + j] = std::round(value * 100) / 100;
		}
	}

	return A;
}

double* InitVectorB(double* A, int N) {
	double* b = (double*)malloc(N * sizeof(double));

	for (int i = 0; i < N; ++i) {
		//double value = (double)rand() / double(RAND_MAX);
		//if (rand() % 2 == 0) value *= -1.0;
		//b[i] = std::round(value * 100) / 100;
		b[i] = i;
	}

	return b;
}

int main() {
	double* A = InitMatrixA(SIZE);
	double* x = InitPreSolution(SIZE);
	double* b = InitVectorB(A, SIZE);

	ConjugateGradientMethod(A, x, b);	
	PrintVector(x, SIZE);

	free(A);
	free(x);
	free(b);
}

	//double A[] = {
	//	1.0, 2.0, 3.0,
	//	4.0, 5.0, 6.0,
	//	7.0, 8.0, 9.0
	//};
	//double x[] = { 0.0, 0.0, 0.0 };
	//double b[] = { 1, 2, 3 };
	//double d[] = { 4, 5, 6 };

