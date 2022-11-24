#include <iostream>
#include <cmath>
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
			float value;
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
	this->matrix = right.matrix;
	this->N = right.N;
	return *this;
}

Matrix& Matrix::operator+=(const Matrix& right) {
	Matrix result = *this + right;
	*this = result;
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& right) {
	for (int i = 0; i < N * N; ++i) {
		this->matrix[i] -= right.matrix[i];
	}
	return *this;
}

Matrix operator*(const Matrix& left, const Matrix& right) {
	int N = left.N;
	Matrix result(N);
	for (int k = 0; k < N; ++k) {
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				result.matrix[i * N + j] += left.matrix[i * N + k] * right.matrix[k * N + j];
			}
		}
	}
	return result;
}

Matrix operator+(const Matrix& left, const Matrix& right) {
	Matrix result(left.N);
	for (int i = 0; i < left.N * left.N; ++i) {
		result.matrix[i] = left.matrix[i] + right.matrix[i];
	}
	return result;
}

Matrix operator-(const Matrix& left, const Matrix& right) {
	int N = left.N;
	Matrix result(N);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			result.matrix[i * N + j] = left.matrix[i * N + j] - right.matrix[i * N + j];
		}
	}
	return result;
}

Matrix operator/(const Matrix& left, float right) {
	Matrix result = left;
	for (int i = 0; i < left.N; ++i) {
		for (int j = 0; j < left.N; ++j) {
			result.matrix[i * left.N + j] /= right;
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
