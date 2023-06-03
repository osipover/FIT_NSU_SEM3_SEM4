#pragma once

enum DefaultParameters {
	DEFAULT_NUM_ROWS = 10,
	DEFAULT_NUM_COLS = 10
}; 

char* CreateFieldWithGlider(int numCols, int numRows);
void StartSimulation(char* currField, int numRows, int numCols);
