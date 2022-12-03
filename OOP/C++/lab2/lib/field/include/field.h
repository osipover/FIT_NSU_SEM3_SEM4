#pragma once
#include <vector>
#include <fstream>
#include "galaxy.h"

class Field {
public:
    Field() : height(0), width(0) {};
    Field(Galaxy&);
    ~Field();
    int getHeight();
    int getWidth();
    void update(Galaxy& galaxy);
    void output();
    void output(std::ofstream& output);
private:
    int height;
    int width;
    std::vector<bool> curField;
    std::vector<bool> nextField;
};
