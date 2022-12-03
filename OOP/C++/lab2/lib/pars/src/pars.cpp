#include "pars.h"

void Pars::commandLine(int argc, char* argv[]) {
    if (argc != 2) {
        throw std::exception("[ERROR] No file for input or too many arguments.");
    }
    this->input.open(argv[1]);
    if (!this->input.is_open()) {
        throw std::exception("[ERROR] I can't open this file.");
    }
}

std::ifstream& Pars::getInput() {
    return this->input;
}
