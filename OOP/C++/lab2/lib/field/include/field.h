#pragma once
#include <vector>
#include <fstream>
#include "life.h"

class Field {
public:
    Field() : size(0) {};
    Field(Galaxy&);
    ~Field();
    bool getCell(int i, int j) const;
    int getSize();
    void update(Galaxy& galaxy);
private:
    int size;
    std::vector<bool> curField;
    std::vector<bool> nextField;
};
