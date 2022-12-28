#include <iostream>
#include <string>
#include <tuple>
#include <fstream>
#include "TupleUtility.h"
#include "CSVParser.h"

int main() {
	std::ifstream file("test3.csv");
	CSVParser<double, int> parser(file, 0 /*skip first lines count*/);
	try {
		for (auto tuple : parser) {
			std::cout << tuple << std::endl;
		}
	}
	catch (IncorrectTypeOfCell& ex) {
		ex.outputDebugMessage();
	}
	return 0;
}
