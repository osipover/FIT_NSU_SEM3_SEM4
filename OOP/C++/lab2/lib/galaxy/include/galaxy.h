#pragma once
#include "life.h"
#include <fstream>
#include <vector>
#include <string>

class Galaxy {
public:
    Galaxy() : size(0), rules(nullptr) {}
    std::vector<bool>& getField();
    int getSize();
    std::string getName();
    Rules& getRules();
    friend void operator >> (std::ifstream& input, Galaxy& galaxy);
private:
    std::vector<bool> field;
    std::string name;
    int size;
    Rules* rules;
};
