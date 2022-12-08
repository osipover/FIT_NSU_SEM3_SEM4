#include <xmmintrin.h>
#include <fstream>
#include <iostream>
#include <cmath>
#define SIZE 2048

class Matrix {
public:
	Matrix();
	Matrix(int N);
	Matrix(int N, std::ifstream& input);
	void init(std::ifstream& input);
	void output();
	int getN();
	float getCell(int i, int j);
	void setCell(int i, int j, float value);
	Matrix transpose();
	Matrix invert(int M);
	Matrix& operator=(const Matrix& right);
	Matrix& operator+=(const Matrix& right);
	Matrix& operator-=(const Matrix& right);
	friend Matrix operator*(const Matrix& left, const Matrix& right);
	friend Matrix operator+(const Matrix& left, const Matrix& right);
	friend Matrix operator-(const Matrix& left, const Matrix& right);
	friend Matrix operator/(Matrix& left, float right);
private:
	float* matrix;
	size_t N;
};

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

Matrix::Matrix(int N, std::ifstream& input) : N(N) {
	matrix = new float[N * N];
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			float value;
			input >> matrix[i * N + j];
		}
	}
	std::cout << "Matrix A is initialized\n";
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
	if (this != &right) {
		this->N = right.N;
		this->matrix = right.matrix;
	}
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
			mult = _mm_set_ps1(left.matrix[i * N + j]);
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

float getA1MultAinf(Matrix& A) {
	float A1 = 0;
	float Ainf = 0;
	for (int j = 0; j < A.getN(); ++j) {
		float curMaxA1 = 0;
		float curMaxAinf = 0;
		for (int i = 0; i < A.getN(); ++i) {
			curMaxA1 += fabs(A.getCell(i, j));
			curMaxAinf += fabs(A.getCell(j, i));
		}
		if (curMaxA1 > A1) A1 = curMaxA1;
		if (curMaxAinf > Ainf) Ainf = curMaxAinf;
	}
	return A1 * Ainf;
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

int main() {
	std::ifstream input;
	input.open("matrix.txt");
	if (input.is_open()) {
		Matrix A(SIZE);
		A.init(input);
		time_t start, end;
		time(&start);
		Matrix I = A.invert(10);
		time(&end);
		Matrix E = A * I;
		std::cout << "Time taken to find matrix I (inverted): " << difftime(end, start) << "sec\n";
		std::cout << "E = A * I\n";
		std::cout << "|E_1| = " << getA1(E) << std::endl;
		std::cout << "|E_inf| = " << getAinf(E) << std::endl;
	}

	return 0;
}
