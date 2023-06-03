#include "mpi.h"
#include "life.h"
#include <stdlib.h>
#include <iostream>
#include <math.h>

int main(int argc, char **argv) {
	const int numRows = (argc > 1 ? atoi(argv[1]) : DEFAULT_NUM_ROWS);
	const int numCols = (argc > 2 ? atoi(argv[2]) : DEFAULT_NUM_COLS);

	char *field = CreateFieldWithGlider(numCols, numRows);

	time_t startTime;
	time(&startTime);
	
	StartSimulation(field, numRows, numCols);
	
	time_t endTime;
	time(&endTime);
	
	double totalTime = difftime(endTime, startTime);
	
	printf("Total time: %f sec\n", totalTime);
}
