#include <string>
#include <iostream>
#include "life.h"

Stream::Stream(int argc, char* argv[]) : numIterat(10) {
	for (int i = 1; i < argc; ++i) {
		if (std::string(argv[i]) == "-i") {
			this->numIterat = std::atoi(argv[i + 1]);
		}
		else if (std::string(argv[i]) == "-o") {
			this->output.open(std::string(argv[i + 1]));
		}
		else if (i == 1) {
			this->input.open(std::string(argv[i]));
		}
	}
}

void Stream::openInFile(const std::string &fileName) {
	input.open(fileName);
}

void Stream::openOutFile(const std::string& fileName) {
	output.open(fileName);
}

void Stream::close() {
	input.close();
	output.close();
}


std::ifstream& Stream::getInFile() {
	return this->input;
}
/*
std::string Stream::getUniverseName() {
	std::string line;
	std::getline(input, line); //#N Classic
	if ((line.size() > 2) && (line[1] == 'N')) {

	}

	
}
*/
