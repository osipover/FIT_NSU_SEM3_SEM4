#pragma once

enum DefaultParameters {
	DEFAULT_NUM_ROWS = 10,
	DEFAULT_NUM_COLS = 10
};

char* CreateFieldWithGlider(int numCols, int numRows);
int* CalcSizesOfParts(int numProc, int numRows, int numCols);
int* CalcDisplsOfParts(int numProc, int *sizesOfParts);
void StartSimulation(char *curPartOfField, int numRows, int numCols, int *sizesOfParts, int numProc, int curcore, char *field, int *displs);
void PrintResult(float totalTime, int numProc);
