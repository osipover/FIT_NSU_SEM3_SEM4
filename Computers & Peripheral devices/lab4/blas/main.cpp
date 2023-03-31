#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <time.h>
#define SIZE 2048

void PrintResults(int totalTime, Matrix& E){
	std::cout << "Time taken to find matrix I (inverted): " << totalTime << "sec\n";
	std::cout << "E = A * I\n";
	std::cout << "|E_1| = " << getA1(E) << std::endl;
	std::cout << "|E_inf| = " << getAinf(E) << std::endl;
}

int main() {
	std::ifstream input;
	input.open("matrix.txt");
	if (input.is_open()) {
		Matrix A(2048);
		A.init(input);
		time_t start, end;
		time(&start);
		Matrix I = A.invert(10);
		time(&end);
		Matrix E = A * I;
		PrintResults(difftime(end, start), E);
	}

	return 0;
}
