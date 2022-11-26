#include "matrix.h"
#include <xmmintrin.h>
#define SIZE 2048

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
