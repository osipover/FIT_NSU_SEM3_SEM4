#include "mpi.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

#define T1 703

enum MatrixDimension {
	N1 = 2400, 
	N2 = 8000,
	N3 = 4800  
};

typedef struct TCoords {
	int x;
	int y;
} TCoords;

typedef struct TGridProcesses {
	int numProc;
	int numRows;
	int numColumns;
	MPI_Comm GridComm;
	MPI_Comm RowComm;
	MPI_Comm ColumnComm;
}TGrid;

void CreateGridComm(MPI_Comm* GridComm, TGrid* grid) {
	int dimension[2] = { grid->numRows, grid->numColumns };
	int periods[2] = { 0, 0 };
	MPI_Cart_create(MPI_COMM_WORLD, 2, dimension, periods, true, GridComm);
}

void CreateRowsComm(MPI_Comm GridComm, MPI_Comm* RowsComm) {
	int subDimension[2] = { false, true };
	MPI_Cart_sub(GridComm, subDimension, RowsComm);
}

void CreateColumnComm(MPI_Comm GridComm, MPI_Comm* ColumnComm) {
	int subDimension[2] = { true, false };
	MPI_Cart_sub(GridComm, subDimension, ColumnComm);
}

double* InitMatrix(string fileWithMatrix, int N, int M) {
	double* matrix = (double*)malloc(N * M * sizeof(double));
	std::ifstream file;
	file.open(fileWithMatrix);
	for (int i = 0; i < N * M; ++i) {
		file >> matrix[i];
	}
	file.close();
	return matrix;
}

void SliceMatrixA(double* A, double* Ap, TGrid* grid, MPI_Comm ColumnComm, MPI_Comm RowsComm, TCoords coords) {
	int sendcount = (N1  / grid->numRows) * N2;
	if (coords.y == 0) {
		MPI_Scatter(A, sendcount, MPI_DOUBLE, Ap, sendcount, MPI_DOUBLE, 0, ColumnComm);
	}
	MPI_Bcast(Ap, sendcount, MPI_DOUBLE, 0, RowsComm);
}

void SliceMatrixB(double* B, double* Bp, int blockSize, MPI_Comm RowsComm, MPI_Comm ColumnComm, TCoords coords) {
	if (coords.x == 0) {
		MPI_Datatype column, columntype;
		MPI_Type_vector(N2, blockSize, N3, MPI_DOUBLE, &column);
		MPI_Type_commit(&column);
		MPI_Type_create_resized(column, 0, blockSize * sizeof(double), &columntype);
		MPI_Type_commit(&columntype);

		MPI_Scatter(B, 1, columntype, Bp, blockSize * N2, MPI_DOUBLE, 0, RowsComm);

		MPI_Type_free(&column);
		MPI_Type_free(&columntype);
	}
	MPI_Bcast(Bp, blockSize * N2, MPI_DOUBLE, 0, ColumnComm);
}

void AssembleMatrixC(double* Cp, double* C, TGrid* grid, MPI_Comm GridComm, int rank) {
	int numRowsInBlock = N1 / grid->numRows;
	int numColumnInBlock = N3 / grid->numColumns;

	MPI_Datatype minor, minortype;

	MPI_Type_vector(numRowsInBlock, numColumnInBlock, N3, MPI_DOUBLE, &minor);
	MPI_Type_commit(&minor);

	MPI_Type_create_resized(minor, 0, numColumnInBlock * sizeof(double), &minortype);
	MPI_Type_commit(&minortype);

	int* rcount = (int*)malloc(grid->numProc * sizeof(int));
	int* displacement = (int*)malloc(grid->numProc * sizeof(int));

	for (int i = 0; i < grid->numRows; ++i) {
		for (int j = 0; j < grid->numColumns; ++j) {
			rcount[i * grid->numColumns + j] = 1;
			displacement[i * grid->numColumns + j] = i * grid->numColumns * numRowsInBlock + j;
		}
	}

	MPI_Gatherv(Cp, numRowsInBlock * numColumnInBlock, MPI_DOUBLE, C, rcount, displacement, minortype, 0, GridComm);

	free(rcount);
	free(displacement);

	MPI_Type_free(&minor);
	MPI_Type_free(&minortype);
}

void MatrixMULT(double* A, double* B, double* C, int L, int M, int N) {
	for (int i = 0; i < L; ++i) {
		for (int k = 0; k < M; ++k) {
			for (int j = 0; j < N; ++j) {
				C[i * N + j] += A[i * M + k] * B[k * N + j];
			}
		}
	}
}

void FreeMemory(double* A, double* B, double* C, double* Ap, double* Bp, double* Cp, int rank) {
	if (rank == 0) {
		free(A);
		free(B);
		free(C);
	}
	free(Ap);
	free(Bp);
	free(Cp);
}

void PrintResult(float totalTime, int numProc, TGrid* grid) {
	float boost = T1 / totalTime;
	float efficiency = (boost / (float)numProc) * 100;
	printf("Number of processes: %d\n", numProc);
	printf("Grid: %d x %d\n", grid->numRows, grid->numColumns);
	printf("Total time: %f sec\n", totalTime);
	printf("Sp = %f\n", boost);
	printf("Ep = %f\n\n", efficiency);
}

int main(int argc, char** argv) {
	int numProc, rank;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numProc);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	TGrid grid;
	grid.numProc = numProc;
	grid.numRows = atoi(argv[1]);
	grid.numColumns = atoi(argv[2]);

	TCoords coords;

	MPI_Comm GridComm;
	CreateGridComm(&GridComm, &grid);

	MPI_Comm RowsComm;
	CreateRowsComm(GridComm, &RowsComm);
	MPI_Comm_rank(RowsComm, &coords.y);

	MPI_Comm ColumnComm;
	CreateColumnComm(GridComm, &ColumnComm);
	MPI_Comm_rank(ColumnComm, &coords.x);

	double* A = NULL;
	double* B = NULL;
	double* C = NULL;

	if ((coords.x == 0) && (coords.y == 0)) {
		A = InitMatrix("A.txt", N1, N2);
		B = InitMatrix("B.txt", N2, N3);
		C = (double*)malloc(N1 * N3 * sizeof(double));
	}

	double startTime = MPI_Wtime();

	int sizeAp = (N1 / grid.numRows) * N2;
	double* Ap = (double*)malloc(sizeAp * sizeof(double));
	SliceMatrixA(A, Ap, &grid, ColumnComm, RowsComm, coords);

	int sizeBp = N2 * (N3 / grid.numColumns);
	double* Bp = (double*)malloc(sizeBp * sizeof(double));
	SliceMatrixB(B, Bp, N3 / grid.numColumns, RowsComm, ColumnComm, coords);

	int sizeCp = (N1 / grid.numRows) * (N3 / grid.numColumns);
	double* Cp = (double*)calloc(sizeCp, sizeof(double));
	MatrixMULT(Ap, Bp, Cp, N1 / grid.numRows, N2, N3 / grid.numColumns);

	AssembleMatrixC(Cp, C, &grid, GridComm, rank);

	double endTime = MPI_Wtime();

	if (rank == 0) {
		PrintResult(endTime - startTime, numProc, &grid);
	}

	FreeMemory(A, B, C, Ap, Bp, Cp, rank);

	MPI_Finalize();
}
