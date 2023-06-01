#include "mpi.h"
#include "life.h"
#include <stdlib.h>
#include <iostream>
#include <math.h>

int main(int argc, char **argv) {
	int numProc;
	int rank;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numProc);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	char *field = NULL;
	const int numRows = (argc > 1 ? atoi(argv[1]) : DEFAULT_NUM_ROWS);
	const int numCols = (argc > 2 ? atoi(argv[2]) : DEFAULT_NUM_COLS);

	if (rank == 0) {
		field = CreateFieldWithGlider(numCols, numRows);
	}

	double startTime = MPI_Wtime();

	int *sizesOfParts = CalcSizesOfParts(numProc, numRows, numCols);
	int *displsOfParts = CalcDisplsOfParts(numProc, sizesOfParts);

	char *partOfField = (char *) malloc(sizesOfParts[rank] * sizeof(char));

	MPI_Scatterv(field, sizesOfParts, displsOfParts, MPI_CHAR, partOfField, sizesOfParts[rank], MPI_CHAR, 0, MPI_COMM_WORLD);

	StartSimulation(partOfField, numRows, numCols, sizesOfParts, numProc, rank, field, displsOfParts);

	double endTime = MPI_Wtime();

	if (rank == 0) {
		PrintResult(endTime - startTime, numProc);
		free(field);
	}

	free(sizesOfParts);
	free(displsOfParts);

	MPI_Finalize();
}
