#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>

#define SIZE 2000
#define EPSILON 0.00001

void PrintVector(double* vector, int N) {
	for (int i = 0; i < N; ++i) {
		printf("%f ", vector[i]);
	}
	printf("\n");
}

void PrintMatrix(double* matrix, int N) {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			printf("%f ", matrix[i * N + j]);
		}
		printf("\n");
	}
	printf("\n");
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

double DotProduct(double* a, double* b) {
	double dot = 0;
	for (int i = 0; i < SIZE; ++i) {
		dot += (a[i] * b[i]);
	}
	return dot;
}

double Norm(double* vector) {
	double norm = 0;
	for (int i = 0; i < SIZE; ++i) {
		norm += (vector[i] * vector[i]);
	}
	return sqrt(norm);
}

double* InitVectorR(double* A, double* x, double* b, double* tmp) {
	double* r = (double*)malloc(SIZE * sizeof(double));
	MatrixMULT(A, x, tmp, SIZE, SIZE, 1);
	MatrixSUB(b, tmp, r, SIZE);
	return r;
}

void CalcNextX(double* x, double* z, double alpha, double* tmp) {
	ScalarMULT(alpha, z, tmp, SIZE);
	MatrixADD(x, tmp, x, SIZE);
}

void CalcNextR(double* A, double* r, double* z, double alpha, double* r_next, double* tmp) {
	MatrixMULT(A, z, tmp, SIZE, SIZE, 1);
	ScalarMULT(alpha, tmp, tmp, SIZE);
	MatrixSUB(r, tmp, r_next, SIZE);
}

void CalcNextZ(double beta, double* r_next, double* z) {
	ScalarMULT(beta, z, z, SIZE);
	MatrixADD(r_next, z, z, SIZE);
}

double CalcNextAlpha(double* A, double* r, double* z, double* tmp) {
	MatrixMULT(A, z, tmp, SIZE, SIZE, 1);
	double alpha = DotProduct(r, r) / DotProduct(tmp, z);
	return alpha;
}

double CalcNextBeta(double* r_next, double* r) {
	return DotProduct(r_next, r_next) / DotProduct(r, r);
}

bool isSolutionReached(double* r, double* b) {
	return (Norm(r) / Norm(b)) < EPSILON;
}

void ConjugateGradientMethod(double* A, double* x, double* b) {
	double* tmp = (double*)malloc(SIZE * sizeof(double));

	double* r = InitVectorR(A, x, b, tmp);
	double* r_next = (double*)malloc(SIZE * sizeof(double));
	double* z = (double*)malloc(SIZE * sizeof(double));

	CopyMatrix(r, z, SIZE);

	double alpha = 0.0;
	double beta = 0.0;

	int count = 0;

	while (!isSolutionReached(r, b) && (count < 50000)) {
		alpha = CalcNextAlpha(A, r, z, tmp);
		CalcNextX(x, z, alpha, tmp);
		CalcNextR(A, r, z, alpha, r_next, tmp);
		beta = CalcNextBeta(r_next, r);
		CalcNextZ(beta, r_next, z);
		CopyMatrix(r_next, r, SIZE);
		++count;
	}
	printf("Number of iterations: %d\n", count);
}

double* InitMatrixA(int N) {
	std::ifstream file;
	file.open("A.txt");

	double* A = (double*)malloc(N * N * sizeof(double));
	for (int i = 0; i < N * N; ++i) {
		file >> A[i];
	}

	file.close();
	return A;
}

double* InitVectorB(double* A, int N) {
	double* b = (double*)malloc(N * sizeof(double));
	for (int i = 0; i < N; ++i) {
		b[i] = i + 1;
	}
	return b;
}

double* InitPreSolution(int N) {
	double* x = (double*)malloc(N * sizeof(double));
	for (int i = 0; i < N; ++i) {
		x[i] = 0.0;
	}
	return x;
}

void GenerateMatrixA(int N) {
	double* A = (double*)malloc(N * N * sizeof(double));
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			double value = (double)rand() / RAND_MAX + (i == j ? (double)SIZE / 100 : 0);
			A[i * N + j] = (i > j ? A[j * N + i] : value);
		}
	}

	std::ofstream fileIn;
	fileIn.open("A.txt");
	if (fileIn.is_open()) {
		for (int i = 0; i < N * N; ++i) {
			fileIn << A[i] << std::endl;
		}
		fileIn.close();
	}
}


int main() {
	GenerateMatrixA(SIZE);

	time_t startTime, endTime;
	time(&startTime);
	double* A = InitMatrixA(SIZE);
	double* x = InitPreSolution(SIZE);
	double* b = InitVectorB(A, SIZE);
	ConjugateGradientMethod(A, x, b);
	time(&endTime);

	printf("Time: %f sec\n\n", difftime(endTime, startTime));

	free(A);
	free(x);
	free(b);
}
