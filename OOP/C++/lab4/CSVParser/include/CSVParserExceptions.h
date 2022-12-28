#pragma once
#include "CSVParser.h"
#include <sstream>
#include <string>
#include <exception>

class IncorrectTypeOfCell : public std::exception {
public:
	IncorrectTypeOfCell(int curLine, int curCell) : curLine(curLine), curCell(curCell) { }
	void outputDebugMessage() {
		std::cerr << "[ERROR] Incorrect line of cell" << std::endl <<
			"Line: " << curLine << std::endl <<
			"Cell: " << curCell << std::endl;
	}

private:
	int curLine;
	int curCell;
};


