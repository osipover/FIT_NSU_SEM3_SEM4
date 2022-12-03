#include <fstream>

class Pars {
public:
    void commandLine(int argc, char* argv[]);
    std::ifstream& getInput();
private:
    std::ifstream input;
};
