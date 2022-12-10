#pragma once
#include <fstream>

class Pars {
public:
    void commandLine(int argc, char* argv[]);
    std::ifstream& getInput();
private:
    std::ifstream input;
};

class ParsExceptions : public std::exception {
public:
    ParsExceptions(const char* msg) :std::exception(msg) {}
private:
};
