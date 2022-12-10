#include <iostream>
#include "ParseCommandLine.h"
int main(int argc, char** argv) {
    ParseCommandLine commandLine(argc, argv);
    std::cout << commandLine.getNumberOfInputFiles();
    return 0;
}
