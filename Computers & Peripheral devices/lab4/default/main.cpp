#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <time.h>
#define SIZE 2048

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
		std::cout << "Time taken to find matrix I (inverted): " << difftime(end, start) << "sec\n";
		std::cout << "E = A * I\n";
		std::cout << "|E_1| = " << getA1(E) << std::endl;
		std::cout << "|E_inf| = " << getAinf(E) << std::endl;
	}

	return 0;
}
