#pragma once
#include "rules.h"
#include <fstream>
#include <vector>
#include <string>

class Galaxy {
public:
    Galaxy() : height(0), width(0){}
    std::vector<bool>& getField();
    int getHeight();
    int getWidth();
    std::string getName();
    Rules& getRules();
    friend void operator >> (std::ifstream& input, Galaxy& galaxy);
private:
    std::vector<bool> field;
    std::string name;
    int height;
    int width;
    Rules rules;
    void parcGalaxyName(std::string& line, std::ifstream& input);
    void parcRules(std::string& line, std::ifstream& input);
    void parcFieldSize(std::string& line, std::ifstream& input);
    std::vector<bool> parcCells(std::string& line, std::ifstream& input);
};
