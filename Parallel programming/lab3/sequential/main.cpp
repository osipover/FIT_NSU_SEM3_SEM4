#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

enum MatrixDimension {
	N1 = 2400, 
	N2 = 7000,
	N3 = 4800 
};

double* InitMatrix(string fileWithMatrix, int N, int M) {
	double* matrix = (double*)malloc(N * M * sizeof(double));
	std::ifstream file;
	file.open(fileWithMatrix);
	for (int i = 0; i < N * M; ++i) {
		file >> matrix[i];
	}
	file.close();
	return matrix;
}

void MatrixMULT(double* A, double* B, double* C, int L, int M, int N) {
	for (int i = 0; i < L; ++i) {
		for (int k = 0; k < M; ++k) {
			for (int j = 0; j < N; ++j) {
				C[i * N + j] += A[i * M + k] * B[k * N + j];
			}
		}
	}
}

void FreeMemory(double* A, double* B, double* C) {
	free(A);
	free(B);
	free(C);
}

int main(int argc, char** argv) {
	double* A = InitMatrix("A.txt", N1, N2);
	double* B = InitMatrix("B.txt", N2, N3);
	double* C = (double*)calloc(N1 * N3, sizeof(double));

	time_t startTime, endTime;

	time(&startTime);

	MatrixMULT(A, B, C, N1, N2, N3);

	time(&endTime);

	printf("Time: %f sec\n", difftime(endTime, startTime));

	FreeMemory(A, B, C);
}
