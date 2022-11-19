#include "matrix.h"

int main() {
	Matrix A(3);
	A.init();
	Matrix I = A.invert(3);
	I.output();
	return 0;
}
