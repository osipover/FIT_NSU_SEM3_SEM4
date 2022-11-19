#pragma once
#include <vector>
#include <iostream>

class Matrix {
public:
	Matrix();
	Matrix(int N);
	void init();
	void output();
	int getN();
	Matrix& operator=(const Matrix& right);
	Matrix& operator+=(const Matrix& right);
	Matrix& operator-=(const Matrix& right);
	Matrix transpose();
	Matrix invert(int M);
	friend Matrix operator*(const Matrix& left, const Matrix& right);
	friend Matrix operator+(const Matrix& left, const Matrix& right);
	friend Matrix operator-(const Matrix& left, const Matrix& right);
	friend Matrix operator/(const Matrix& left, float right);
	float* matrix;
private:
	size_t N;
};
