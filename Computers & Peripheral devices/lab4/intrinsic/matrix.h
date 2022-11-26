#pragma once
#include <vector>
#include <iostream>
#include <fstream>

class Matrix {
public:
	Matrix();
	Matrix(int N);
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
