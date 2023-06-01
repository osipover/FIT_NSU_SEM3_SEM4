#pragma once

#include "life.h"
#include <iostream>
#include "mpi.h"

#define NUM_ITER 50000
#define T1 67.0

void PrintField(char *field, int numRows, int numCols) {
	for (int i = 0; i < numRows; ++i) {
		for (int j = 0; j < numCols; ++j) {
			std::cout << (field[i * numCols + j] == 1 ? "#" : ".") << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

char* CreateFieldWithGlider(int numCols, int numRows) {
	char* field = (char*)calloc(numCols * numRows, sizeof(char));
	field[0 * numCols + 1] = 1;
	field[1 * numCols + 2] = 1;
	field[2 * numCols + 0] = 1;
	field[2 * numCols + 1] = 1;
	field[2 * numCols + 2] = 1;
	return field;
}

int* CalcSizesOfParts(int numProc, int numRows, int numCols) {
	int *sizesOfParts = (int*)malloc(numProc * sizeof(int));
	double step = (double)numRows / numProc;
	double countLines = step;
	int numLinesOfPart = 0;
	int countBusyLines = 0;
	for (int i = 0; i < numProc; ++i) {
		numLinesOfPart = ceil(countLines) - countBusyLines;
		sizesOfParts[i] = numLinesOfPart * numCols;
		countBusyLines += numLinesOfPart;
		countLines += step;
	}
	return sizesOfParts;
}

int* CalcDisplsOfParts(int numProc, int* sizesOfParts) {
	int *displsOfParts = (int *) malloc(numProc * sizeof(int));
	int curOffset = 0;
	for (int i = 0; i < numProc; ++i) {
		displsOfParts[i] = curOffset;
		curOffset += sizesOfParts[i];
	}
	return displsOfParts;
}

void CalcVectorOfStopFlags(char *stopflags, char **prevPartOfFields, char *curPartOfField, int sizeOfPart, int curIter) {
	int numFlags = curIter - 1;
	for (int i = 0; i < numFlags; ++i) {
		stopflags[i] = 1;
		for (int j = 0; j < sizeOfPart; ++j) {
			if (prevPartOfFields[i][j] != curPartOfField[j]) {
				stopflags[i] = 0;
				break;
			}
		}
	}
}

int GetNumOfAliveNeighborsInCentre(char *curPartOfField, int x, int y, int numRowsInCore, int numCols) {
	int numNeighbors = 0;

	int prevx = (x - 1 + numCols) % numCols;
	int nextx = (x + 1 + numCols) % numCols;

	int prevy = (y - 1 + numRowsInCore) % numRowsInCore;
	int nexty = (y + 1 + numRowsInCore) % numRowsInCore;

	numNeighbors += curPartOfField[prevy * numCols + prevx];
	numNeighbors += curPartOfField[prevy * numCols + x];
	numNeighbors += curPartOfField[prevy * numCols + nextx];

	numNeighbors += curPartOfField[y * numCols + prevx];
	numNeighbors += curPartOfField[y * numCols + nextx];

	numNeighbors += curPartOfField[nexty * numCols + prevx];
	numNeighbors += curPartOfField[nexty * numCols + x];
	numNeighbors += curPartOfField[nexty * numCols + nextx];

	return numNeighbors;
}

bool isAlive(char *curPartOfField, int x, int y, int numCols) {
	if (curPartOfField[x + y * numCols] == 1) return true;
	return false;
}

bool isSurvived(int numNeighbors) {
	if (numNeighbors == 2 || numNeighbors == 3) return true;
	return false;
}

bool isBorn(int numNeighbors) {
	if (numNeighbors == 3) return true;
	return false;
}

void CalcNextGenerationInCentre(char *newPartOfField, char *curPartOfField, int numRowsInCore, int numCols) {
	int numNeighbors = 0;
	for (int y = 1; y < numRowsInCore - 1; ++y) {
		for (int x = 0; x < numCols; ++x) {
			numNeighbors = GetNumOfAliveNeighborsInCentre(curPartOfField, x, y, numRowsInCore, numCols);
			bool keepAlive = isAlive(curPartOfField, x, y, numCols) && isSurvived(numNeighbors);
			bool becomeAlive = !isAlive(curPartOfField, x, y, numCols) && isBorn(numNeighbors);
			newPartOfField[x + y * numCols] = (keepAlive || becomeAlive == true ? 1 : 0);
		}
	}
}

int GetNumOfAliveNeighborsInRow(char *curPartOfField, char *recvRow, int x, int y, int numCols, int numRowsInCore, int rank) {
	int numNeighbors = 0;

	int prevx = (x - 1 + numCols) % numCols;
	int nextx = (x + 1 + numCols) % numCols;

	numNeighbors += curPartOfField[y * numCols + prevx];
	numNeighbors += curPartOfField[y * numCols + nextx];

	numNeighbors += recvRow[prevx];
	numNeighbors += recvRow[x];
	numNeighbors += recvRow[nextx];

	if (y == 0) {
		numNeighbors += curPartOfField[1 * numCols + prevx];
		numNeighbors += curPartOfField[1 * numCols + x];
		numNeighbors += curPartOfField[1 * numCols + nextx];
	}
	else {
		numNeighbors += curPartOfField[(y - 1) * numCols + prevx];
		numNeighbors += curPartOfField[(y - 1) * numCols + x];
		numNeighbors += curPartOfField[(y - 1) * numCols + nextx];
	}

	return numNeighbors;
}

void CalcNextGenerationInRow(char *newPartOfField, char *curPartOfField, char *recvRow, int y, int numRowsInCore, int numCols, int rank) {
	int numNeighbors = 0;
	for (int x = 0; x < numCols; ++x) {
		numNeighbors = GetNumOfAliveNeighborsInRow(curPartOfField, recvRow, x, y, numCols, numRowsInCore, rank);
		bool keepAlive = isAlive(curPartOfField, x, y, numCols) && isSurvived(numNeighbors);
		bool becomeAlive = !isAlive(curPartOfField, x, y, numCols) && isBorn(numNeighbors);
		newPartOfField[x + y * numCols] = (keepAlive || becomeAlive == true ? 1 : 0);
	}
}

bool IsMatchFound(char *exchStopFlags, int sizeOfIterBlock, int numPassedIter, int numProc) {
	int flagOfMatch = 0;
	for (int i = 0; i < sizeOfIterBlock; ++i) {
		int countOnes = 0;
		for (int j = 0; j < numProc; ++j) {
			countOnes += exchStopFlags[i + j * sizeOfIterBlock];
		}
		if (countOnes == numProc) {
			flagOfMatch = 1;
			break;
		}
	}
	int numMatches = 0;
	MPI_Allreduce(&flagOfMatch, &numMatches, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

	if (numMatches >= 1) return true;
	return false;
}

void StartSimulation(char *curPartOfField, int numRows, int numCols, int *sizesOfParts, int numProc, int curcore, char *field, int *displs) {
	char **prevPartOfFields = (char **)malloc(NUM_ITER * sizeof(char*));

	char *stopFlags = (char *) calloc(NUM_ITER, sizeof(char));
	char *exchStopFlags = (char *) calloc(NUM_ITER, sizeof(char));

	int numRowsInCore = sizesOfParts[curcore] / numCols;

	int prevCore = (curcore == 0 ? numProc - 1 : curcore - 1);
	int nextCore = (curcore == numProc - 1 ? 0 : curcore + 1);

	char *lineFromPrevCore = (char *) malloc(numCols * sizeof(char));
	char *lineFromNextCore = (char *) malloc(numCols * sizeof(char));

	MPI_Request reqSendPrev;
	MPI_Request reqSendNext;
	MPI_Request reqRecvPrev;
	MPI_Request reqRecvNext;
	MPI_Request reqFlags;

	int countIter;

	for (countIter = 1; countIter <= NUM_ITER; ++countIter) {

		int numPassedIter = countIter - 1;

		MPI_Isend(curPartOfField, numCols, MPI_CHAR, prevCore, 0, MPI_COMM_WORLD, &reqSendPrev);

		int shiftToLastLine = sizesOfParts[curcore] - numCols;
		MPI_Isend(curPartOfField + shiftToLastLine, numCols, MPI_CHAR, nextCore, 0, MPI_COMM_WORLD, &reqSendNext);

		MPI_Irecv(lineFromPrevCore, numCols, MPI_CHAR, prevCore, MPI_ANY_TAG, MPI_COMM_WORLD, &reqRecvPrev);

		MPI_Irecv(lineFromNextCore, numCols, MPI_CHAR, nextCore, MPI_ANY_TAG, MPI_COMM_WORLD, &reqRecvNext);

		CalcVectorOfStopFlags(stopFlags, prevPartOfFields, curPartOfField, sizesOfParts[curcore], countIter);

		int sizeOfIterBlock = ceil((double)numPassedIter / numProc);
		MPI_Ialltoall(stopFlags, sizeOfIterBlock, MPI_CHAR, exchStopFlags, sizeOfIterBlock, MPI_CHAR, MPI_COMM_WORLD, &reqFlags);

		char *newPartOfField = (char *) malloc(sizesOfParts[curcore] * sizeof(char));

		CalcNextGenerationInCentre(newPartOfField, curPartOfField, numRowsInCore, numCols);

		MPI_Wait(&reqSendPrev, MPI_STATUS_IGNORE);

		MPI_Wait(&reqRecvPrev, MPI_STATUS_IGNORE);

		CalcNextGenerationInRow(newPartOfField, curPartOfField, lineFromPrevCore, 0, numRowsInCore, numCols, curcore);

		MPI_Wait(&reqSendNext, MPI_STATUS_IGNORE);

		MPI_Wait(&reqRecvNext, MPI_STATUS_IGNORE);

		CalcNextGenerationInRow(newPartOfField, curPartOfField, lineFromNextCore, numRowsInCore - 1, numRowsInCore, numCols, curcore);

		MPI_Wait(&reqFlags, MPI_STATUS_IGNORE);

		if (IsMatchFound(exchStopFlags, sizeOfIterBlock, numPassedIter, numProc)) {
			--countIter;
			break;
		}
		prevPartOfFields[numPassedIter] = curPartOfField;
		curPartOfField = newPartOfField;
	}

	if (curcore == 0) {
		std::cout << "Total iterations: " << countIter << std::endl;
	}

	for (int i = 0; i < countIter; ++i) {
		free(prevPartOfFields[i]);
	}
	free(prevPartOfFields);
	free(stopFlags);
	free(exchStopFlags);
	free(lineFromNextCore);
	free(lineFromPrevCore);
}

void PrintResult(float totalTime, int numProc) {
	float boost = T1 / totalTime;
	float efficiency = (boost / (float)numProc) * 100;
	printf("Number of processes: %d\n", numProc);
	printf("Total time: %f sec\n", totalTime);
	printf("Sp = %f\n", boost);
	printf("Ep = %f\n\n", efficiency);
}
