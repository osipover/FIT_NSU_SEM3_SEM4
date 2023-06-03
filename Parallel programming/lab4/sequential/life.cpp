#include <stdlib.h>
#include <iostream>

#define NUM_ITER 50000

char* CreateFieldWithGlider(int numCols, int numRows) {
	char* field = (char*)calloc(numCols * numRows, sizeof(char));

	field[0 * numCols + 1] = 1;
	field[1 * numCols + 2] = 1;
	field[2 * numCols + 0] = 1;
	field[2 * numCols + 1] = 1;
	field[2 * numCols + 2] = 1;

	return field;
}

bool IsMatchFound(char** prevFields, char* curField, int sizeField, int numPassedIter) {
	for (int i = 0; i < numPassedIter; ++i) {
		bool isMatchDetected = true;
		for (int j = 0; j < sizeField; ++j) {
			if (prevFields[i][j] != curField[j]) {
				isMatchDetected = false;
				break;
			}
		}
		if (isMatchDetected) return true;
	}
	return false;
}

int GetNumOfAliveNeighborsInCentre(char* curPartOfField, int x, int y, int numRowsInCore, int numCols) {
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

bool isAlive(char* curPartOfField, int x, int y, int numCols) {
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

void CalcNextGeneration(char* newPartOfField, char* curPartOfField, int numRows, int numCols) {
	int numNeighbors = 0;
	for (int y = 0; y < numRows; ++y) {
		for (int x = 0; x < numCols; ++x) {
			numNeighbors = GetNumOfAliveNeighborsInCentre(curPartOfField, x, y, numRows, numCols);
			bool keepAlive = isAlive(curPartOfField, x, y, numCols) && isSurvived(numNeighbors);
			bool becomeAlive = !isAlive(curPartOfField, x, y, numCols) && isBorn(numNeighbors);
			newPartOfField[x + y * numCols] = (keepAlive || becomeAlive == true ? 1 : 0);
		}
	}
}
void StartSimulation(char* currField, int numRows, int numCols) {
	char** prevFields = (char**)malloc(NUM_ITER * sizeof(char*));
	int countIter;
	for (countIter = 1; countIter <= NUM_ITER; ++countIter) {
		int numPassedIter = countIter - 1;
		char* nextField = (char*)malloc(numRows * numCols * sizeof(char));
		CalcNextGeneration(nextField, currField, numRows, numCols);

		if (IsMatchFound(prevFields, currField, numRows * numCols, numPassedIter)) {
			--countIter;
			break;
		}

		prevFields[numPassedIter] = currField;
		currField = nextField;
	}

	printf("Total iterations: %d\n", countIter);

	for (int i = 0; i < countIter; ++i) {
		free(prevFields[i]);
	}
	free(prevFields);
}
