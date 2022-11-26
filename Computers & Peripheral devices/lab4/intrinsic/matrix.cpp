#include <iostream>
#include <cmath>
#include <xmmintrin.h>
#include "matrix.h"

Matrix::Matrix() : matrix(nullptr), N(0) {
}

Matrix::Matrix(int N) : N(N) {
	matrix = new float[N * N];

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			matrix[i * N + j] = 0;
		}
	}
}

int Matrix::getN() {
	return N;
}

void Matrix::init(std::ifstream& input) {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			input >> matrix[i * N + j];
		}
	}
	std::cout << "Matrix is initialized\n";
}

void Matrix::output() {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			std::cout << matrix[i * N + j] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

Matrix& Matrix::operator=(const Matrix& right) {
	if (this == &right) {
		return *this;
	}
	this->matrix = right.matrix;
	this->N = right.N;
	return *this;
}

Matrix& Matrix::operator+=(const Matrix& right) {
	*this = *this + right;
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& right) {
	*this = *this - right;
	return *this;
}

Matrix operator*(const Matrix& left, const Matrix& right) {
	int N = left.N;
	__m128* m128_right = (__m128*)right.matrix;
	Matrix result(N);
	__m128* m128_result = (__m128*)result.matrix;
	__m128 mult;
	__m128 tmp;

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			mult = _mm_set1_ps(left.matrix[i * N + j]);
			for (int k = 0; k < N / 4; ++k) {
				tmp = _mm_mul_ps(mult, m128_right[N * j / 4 + k]);
				m128_result[N * i / 4 + k] = _mm_add_ps(m128_result[N * i / 4 + k], tmp);
			}
		}
	}
	return result;
}

Matrix operator+(const Matrix& left, const Matrix& right) {
	Matrix result(left.N);
	__m128* m128_result = (__m128*)result.matrix;
	__m128* m128_left = (__m128*)left.matrix;
	__m128* m128_right = (__m128*)right.matrix;
	for (int i = 0; i < left.N * left.N / 4; ++i) {
		m128_result[i] = _mm_add_ps(m128_left[i], m128_right[i]);
	}
	return result;
}

Matrix operator-(const Matrix& left, const Matrix& right) {
	Matrix result(left.N);
	__m128* m128_result = (__m128*)result.matrix;
	__m128* m128_left = (__m128*)left.matrix;
	__m128* m128_right = (__m128*)right.matrix;
	for (int i = 0; i < left.N * left.N / 4; ++i) {
		m128_result[i] = _mm_sub_ps(m128_left[i], m128_right[i]);
	}
	return result;
}

Matrix operator/(Matrix& left, float right) {
	Matrix result(left.getN());
	for (int i = 0; i < result.getN(); ++i) {
		for (int j = 0; j < result.getN(); ++j) {
			result.setCell(i, j, left.getCell(i, j) / right);
		}
	}
	return result;
}

Matrix Matrix::transpose() {
	Matrix T(N);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			T.matrix[i * N + j] = this->matrix[j * N + i];
		}
	}
	return T;
}

float Matrix::getCell(int i, int j) {
	return this->matrix[i * N + j];
}

void Matrix::setCell(int i, int j, float value) {
	this->matrix[i * N + j] = value;
}

float getA1(Matrix& A) {
	Matrix trA = A.transpose();
	float A1 = 0;
	for (int i = 0; i < A.getN(); ++i) {
		float curMax = 0;
		for (int j = 0; j < A.getN(); ++j) {
			curMax += fabs(trA.getCell(i, j));
		}
		if (curMax > A1) A1 = curMax;
	}
	return A1;
}

float getAinf(Matrix& A) {
	float Ainf = 0;
	for (int i = 0; i < A.getN(); ++i) {
		float curMax = 0;
		for (int j = 0; j < A.getN(); ++j) {
			curMax += fabs(A.getCell(i, j));
		}
		if (curMax > Ainf) Ainf = curMax;
	}
	return Ainf;
}

Matrix createMatrixB(Matrix& A) {
	Matrix B(A.getN());
	Matrix At = A.transpose();
	float A1 = getA1(A);
	float Ainf = getAinf(A);
	B = At / (A1 * Ainf);
	return B;
}

Matrix createMatrixI(int N) {
	Matrix I(N);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			I.setCell(i, j, static_cast<float>(i == j));
		}
	}
	return I;
}

Matrix Matrix::invert(int M) {
	Matrix B = createMatrixB(*this);
	Matrix I = createMatrixI(B.getN());
	Matrix R = I - B * (*this);
	Matrix powR = R;

	Matrix result = I;
	for (int i = 0; i < M; ++i) {
		result += R;
		R = powR * R;
	}

	result = result * B;

	return result;
}
