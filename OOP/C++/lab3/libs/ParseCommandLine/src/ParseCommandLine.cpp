#include "ParseCommandLine.h"
#include <iostream>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

ParseCommandLine::ParseCommandLine(int argc, char** argv) {
	po::options_description desc("Description");
	desc.add_options()
		("help, h", "All available options")
		("config, c", po::value<std::string>(&configFile), "File with a configuration of the programme")
		("input, i", po::value<std::vector<std::string>>(&inputFiles)->multitoken(), "List of the input files with WAV format | -i input1.wav, input2.wav ...")
		("output, o", po::value<std::string>(&outputFile), "Output file");
	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (vm.count("help")) {
		std::cout << desc << std::endl;
	}
}

std::string ParseCommandLine::getConfigFile() {
	return this->configFile;
}

std::vector<std::string>& ParseCommandLine::getInputFiles() {
	return this->inputFiles;
}

std::string ParseCommandLine::getInputFile(int index) {
	return this->inputFiles[index];
}

std::string ParseCommandLine::getOutputFile() {
	return this->outputFile;
}

int ParseCommandLine::getNumberOfInputFiles() {
	return this->inputFiles.size();
}
