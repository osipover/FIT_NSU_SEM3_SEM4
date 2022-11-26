#include <fstream>
#include <cmath>
#include "matrix.h"
#define SIZE 2048

void SetRandValues(int N) {
	std::ofstream input;
	input.open("matrix.txt");
	if (input.is_open()) {
		for (int i = 0; i < N; ++i) {
			float value = (float)rand() / float(RAND_MAX % 1000);
			if (rand() % 2 == 0) {
				value *= -1.0;
			}
			input << std::round(value * 100)/100 << std::endl;
		}
	}
}

int main() {
	std::ifstream input;
	input.open("matrix.txt");
	if (input.is_open()) {
		Matrix A(SIZE);
		A.init(input);
		Matrix I = A.invert(10);
	}

	return 0;
}
