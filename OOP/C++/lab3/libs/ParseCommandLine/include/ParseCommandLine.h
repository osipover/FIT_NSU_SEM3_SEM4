#pragma once
#include <vector>
#include <string>

class ParseCommandLine {
public:
	ParseCommandLine(int argc, char** argv);
	std::string getConfigFile();
	std::string getOutputFile();
	std::string getInputFile(int index);
	int getNumberOfInputFiles();
	std::vector<std::string>& getInputFiles();
private:
	std::string configFile;
	std::string outputFile;	
	std::vector<std::string> inputFiles;
};
