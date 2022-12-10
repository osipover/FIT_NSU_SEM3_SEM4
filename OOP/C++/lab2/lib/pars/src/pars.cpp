#include "pars.h"

void Pars::commandLine(int argc, char* argv[]) {
    if (argc != 2) {
        throw ParsExceptions("[ERROR] No file for input or too many arguments.");
    }
    this->input.open(argv[1]);
    if (!this->input.is_open()) {
        throw ParsExceptions("[ERROR] I can't open this file.");
    }
}

std::ifstream& Pars::getInput() {
    return this->input;
}
