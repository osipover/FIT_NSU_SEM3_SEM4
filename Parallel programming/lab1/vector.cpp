#include "mpi.h"
#include <iostream>
#include <vector>
#include <cmath>
#define SIZE 3
#define EPSILON 0.0001

void PrintVector(std::vector<double>& vector, int N) {
	for (int i = 0; i < N; ++i) {
		std::cout << vector[i] << " ";
	}
	std::cout << std::endl;
}

void CopyMatrix(std::vector<double>& source, std::vector<double>& purpose, int size) {
	for (int i = 0; i < size; ++i) {
		purpose[i] = source[i];
	}
}

void MatrixMULT(const std::vector<double>& A, const std::vector<double>& B, std::vector<double>& C, int L, int M, int N) {
	for (int i = 0; i < L; ++i) {
		for (int j = 0; j < N; ++j) {
			for (int k = 0; k < M; ++k) {
				C[i * N + j] += A[i * M + k] * B[k * N + j];
			}
		}
	}
}

void MatrixSUB(std::vector<double>& A, std::vector<double>& B, std::vector<double>& C, int N) {
	for (int i = 0; i < N; ++i) {
		C[i] = A[i] - B[i];
	}
}

std::vector<double> InitVectorR(std::vector<double>& A, std::vector<double>& x, std::vector<double>& b) {
	std::vector<double> r(SIZE, 0.0);
	std::vector<double> tmp(SIZE, 0.0);
	MatrixMULT(A, x, tmp, SIZE, SIZE, 1);
	MatrixSUB(b, tmp, r, SIZE);
	return r;
}

double DotProduct(const std::vector<double>& a, const std::vector<double>& b) {
	double dot = 0.0;
	for (int i = 0; i < SIZE; ++i) {
		dot += a[i] * b[i];
	}
	return dot;
}

double Norm(std::vector<double>& vector) {
	double norm = 0.0;
	for (int i = 0; i < SIZE; ++i) {
		norm += (vector[i] * vector[i]);
	}
	return std::sqrt(norm);
}

bool isSolutionReached(std::vector<double>& r, std::vector<double>& b) {
	return (Norm(r) / Norm(b)) < EPSILON;
}

double CalcNextAlpha(std::vector<double>& A, std::vector<double>& r, std::vector<double>& z) {
	std::vector<double> tmp(SIZE, 0.0);
	MatrixMULT(A, z, tmp, SIZE, SIZE, 1);
	double alpha = DotProduct(r, r) / DotProduct(tmp, z);
	return alpha;
}

double CalcNextBeta(std::vector<double>& r_next, std::vector<double>& r) {
	return DotProduct(r_next, r_next) / DotProduct(r, r);
}

void ScalarMULT(double scalar, std::vector<double>& matrix, std::vector<double>& result, int N) {
	for (int i = 0; i < N; ++i) {
		result[i] = scalar * matrix[i];
	}
}

void MatrixADD(std::vector<double>& A, std::vector<double>& B, std::vector<double>& C, int N) {
	for (int i = 0; i < N; ++i) {
		C[i] = A[i] + B[i];
	}
}

void CalcNextX(std::vector<double>& x, std::vector<double>& z, double alpha) {
	std::vector<double> tmp(SIZE, 0.0);
	ScalarMULT(alpha, z, tmp, SIZE);
	MatrixADD(x, tmp, x, SIZE); 
}

void CalcNextR(std::vector<double>& A, std::vector<double>& r, std::vector<double>& z, double alpha, std::vector<double>& r_next) {
	std::vector<double> tmp(SIZE, 0.0);
	MatrixMULT(A, z, tmp, SIZE, SIZE, 1);
	ScalarMULT(alpha, tmp, tmp, SIZE);
	MatrixSUB(r, tmp, r_next, SIZE); 
}

void CalcNextZ(double beta, std::vector<double>& r_next, std::vector<double>& z) {
	ScalarMULT(beta, z, z , SIZE);
	MatrixADD(r_next, z, z, SIZE);
}

void ConjugateGradientMethod(std::vector<double>& A, std::vector<double>& x, std::vector<double>& b) {
	std::vector<double> r = InitVectorR(A, x, b);
	std::vector<double> r_next(SIZE);
	std::vector<double> z(SIZE);
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

std::vector<double> InitMatrixA(int N) {
	std::vector<double> A(N*N);

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			A[i * N + j] = (i == j ? 2.0 : 1);
		}
	}

	return A;
}

std::vector<double> InitVectorB(std::vector<double>& A, int N) {
	std::vector<double> b(N, N+1);
	std::vector<double> u(N);
	for (int i = 0; i < N; ++i) {
		u[i] = std::sin((2 * 3.14 * i) / N);
	}
	//MatrixMULT(A, u, b, SIZE, SIZE, 1);

	return b;
}

int main() {
	std::vector<double> A = { 1, 2, 3, 4, 5, 6, 7, 8, 9};//InitMatrixA(SIZE);
	std::vector<double> x(SIZE, 0.0);
	std::vector<double> b = { 1, 2, 3 };//InitVectorB(A, SIZE);

	ConjugateGradientMethod(A, x, b);	
	PrintVector(x, SIZE);
}

	//double A[] = {
	//	1.0, 2.0, 3.0,
	//	4.0, 5.0, 6.0,
	//	7.0, 8.0, 9.0
	//};
	//double x[] = { 0.0, 0.0, 0.0 };
	//double b[] = { 1, 2, 3 };
	//double d[] = { 4, 5, 6 };

