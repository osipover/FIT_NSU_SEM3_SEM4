#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>

#define SIZE 1500
#define EPSILON 0.00001
#define T1 60.8

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
#pragma omp for 
	for (int i = 0; i < size; ++i) {
		purpose[i] = source[i];
	}

}

void MatrixMULT(double* A, double* B, double* C, int L, int M, int N) {
#pragma omp for 
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
#pragma omp for 
	for (int i = 0; i < N; ++i) {
		C[i] = A[i] - B[i];
	}
}

void MatrixADD(double* A, double* B, double* C, int N) {
#pragma omp for 
	for (int i = 0; i < N; ++i) {
		C[i] = A[i] + B[i];
	}
}

void ScalarMULT(double scalar, double* matrix, double* result, int N) {
#pragma omp for 
	for (int i = 0; i < N; ++i) {
		result[i] = scalar * matrix[i];
	}
}

void DotProduct(double* a, double* b, double* dot) {
#pragma omp single
	*dot = 0.0;
#pragma omp for reduction(+:dot[0]) 
	for (int k = 0; k < SIZE; ++k) {
		dot[0] += (a[k] * b[k]);
	}
}

void Norm(double* vector, double* norm) {
#pragma omp single
	*norm = 0.0;
#pragma omp for reduction(+:norm[0])
	for (int k = 0; k < SIZE; ++k) {
		norm[0] += (vector[k] * vector[k]);
	}
#pragma omp single
	*norm = sqrt(*norm);
}

void InitVectorR(double* r, double* A, double* x, double* b, double* tmp) {
	MatrixMULT(A, x, tmp, SIZE, SIZE, 1);
	MatrixSUB(b, tmp, r, SIZE);
}

void CalcNextX(double* x, double* z, double alpha, double* tmp) {
	ScalarMULT(alpha, z, tmp, SIZE);
	MatrixADD(x, tmp, x, SIZE);
}

void CalcNextR(double* A, double* r, double* z, double alpha, double* r_next, double* tmpVector) {
	MatrixMULT(A, z, tmpVector, SIZE, SIZE, 1);
	ScalarMULT(alpha, tmpVector, tmpVector, SIZE);
	MatrixSUB(r, tmpVector, r_next, SIZE);
}

void CalcNextZ(double beta, double* r_next, double* z) {
	ScalarMULT(beta, z, z, SIZE);
	MatrixADD(r_next, z, z, SIZE);
}

void CalcNextAlpha(double* alpha, double* A, double* r, double* z, double* tmpVector, double* tmpValues) {
	MatrixMULT(A, z, tmpVector, SIZE, SIZE, 1);
	DotProduct(r, r, &tmpValues[0]);
	DotProduct(tmpVector, z, &tmpValues[1]);
#pragma omp single
	*alpha = tmpValues[0] / tmpValues[1];
}

void CalcNextBeta(double* beta, double* r_next, double* r, double* tmpValues) {
	DotProduct(r_next, r_next, &tmpValues[0]);
	DotProduct(r, r, &tmpValues[1]);
#pragma omp single 
	*beta = tmpValues[0] / tmpValues[1];
}

bool isSolutionReached(double* r, double* b, double* norms) {
	Norm(r, &norms[0]);
	Norm(b, &norms[1]);
#pragma omp barier 
	return (norms[0] / norms[1]) < EPSILON;
}

void ConjugateGradientMethod(double* A, double* x, double* b, int numThreads) {
	double* r = (double*)malloc(SIZE * sizeof(double));
	double* r_next = (double*)malloc(SIZE * sizeof(double));
	double* z = (double*)malloc(SIZE * sizeof(double));
	double* tmpVector = (double*)malloc(SIZE * sizeof(double));
	double tmpValues[2];

	double alpha = 0.0;
	double beta = 0.0;

	int count = 0;

#pragma omp parallel num_threads(numThreads)
	{
		InitVectorR(r, A, x, b, tmpVector);
		CopyMatrix(r, z, SIZE);

		for (count = 0; count < 50000; ++count) {
			if (isSolutionReached(r, b, tmpValues)) break;
			CalcNextAlpha(&alpha, A, r, z, tmpVector, tmpValues);
			CalcNextX(x, z, alpha, tmpVector);
			CalcNextR(A, r, z, alpha, r_next, tmpVector);
			CalcNextBeta(&beta, r_next, r, tmpValues);
			CalcNextZ(beta, r_next, z);
			CopyMatrix(r_next, r, SIZE);
		}
	}
	free(r);
	free(r_next);
	free(z);
	free(tmpVector);
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

double* InitVectorB(int N) {
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

void PrintResult(int numThreads, double totalTime) {
	float boost = T1 / totalTime;
	float efficiency = (boost / (float)numThreads) * 100;

	printf("Number of threads: %d\n", numThreads);
	printf("Total time: %f sec\n", totalTime);
	printf("Boost: %f\n", boost);
	printf("Efficiency: %f %\n\n", efficiency);
}


int main(int argc, char** argv) {
	int numThreads = (argc > 1 ? atoi(argv[1]) : 1);

	double startTime = omp_get_wtime();

	double* A = InitMatrixA(SIZE);
	double* x = InitPreSolution(SIZE);
	double* b = InitVectorB(SIZE);

	ConjugateGradientMethod(A, x, b, numThreads);

	double endTime = omp_get_wtime();

	PrintResult(numThreads, endTime - startTime);

	free(A);
	free(x);
	free(b);
}
