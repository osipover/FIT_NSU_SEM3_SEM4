#include <iostream>
#include <algorithm>
#include <regex>
#include "life.h"

namespace  {
    bool isSurvived(int numNeighbors, const std::map<int, char>& survivalRules) {
        for (auto it = survivalRules.begin(); it != survivalRules.end(); ++it) {
            if (numNeighbors < it->first) return false;
            if (numNeighbors == it->first) return true;
        }
        return false;
    }

    bool isBorn(int numNeighbors, const std::map<int, char>& birthRules) {
        for (auto it = birthRules.begin(); it != birthRules.end(); ++it) {
            if (numNeighbors < it->first) return false;
            if (numNeighbors == it->first) return true;
        }
        return false;
    }

    bool isAlive(bool cell) {
        if (cell == true) return true;
        else return false;
    }

    int getUpperNeighbor(const std::vector<bool>& field, int pos, int height, int width) {
        if (pos < width) {
            return field[height * width - width + pos] ? 1 : 0;
        }
        else {
            return field[pos - width] ? 1 : 0;
        }
    }

    int getUpperRightNeighbor(const std::vector<bool>& field, int pos, int height, int width) {
        if ((pos < width) || ((pos + 1) % width == 0)) {
            return 0;
        }
        else {
            return field[pos - width + 1] ? 1 : 0;
        }
    }

    int getRightNeighbor(const std::vector<bool>& field, int pos, int height, int width) {
        if ((pos + 1) % width == 0) {
            return field[pos - width + 1] ? 1 : 0;
        }
        else {
            return field[pos + 1] ? 1 : 0;
        }
    }

    int getBottomRightNeighbor(const std::vector<bool>& field, int pos, int height, int width) {
        if (((pos + 1) % width == 0) || (pos >= (height * width - width))) {
            return 0;
        }
        else {
            return field[pos + width + 1] ? 1 : 0;
        }
    }

    int getBottomNeighbor(const std::vector<bool>& field, int pos, int height, int width) {
        if (pos >= (height * width - width)) {
            return field[(pos + width) % (width * height)] ? 1 : 0;
        }
        else {
            return field[pos + width] ? 1 : 0;
        }
    }

    int getBottomLeftNeighbor(const std::vector<bool>& field, int pos, int height, int width) {
        if ((pos % width == 0) || (pos >= (height * width - width))) {
            return 0;
        }
        else {
            return field[pos + width - 1] ? 1 : 0;
        }
    }

    int getLeftNeighbor(const std::vector<bool>& field, int pos, int height, int width) {
        if (pos % width == 0) {
            return field[pos + width - 1] ? 1 : 0;
        }
        else {
            return field[pos - 1] ? 1 : 0;
        }
    }

    int getUpperLeftNeighbor(const std::vector<bool>& field, int pos, int height, int width) {
        if ((pos % width == 0) || (pos < width)) {
            return 0;
        }
        else {
            return field[pos - width - 1] ? 1 : 0;
        }
    }

    int getNumNeighbors(const std::vector<bool>& field, int pos, int height, int width) {
        return getUpperNeighbor(field, pos, height, width) +
             + getUpperRightNeighbor(field, pos, height, width) +
             + getRightNeighbor(field, pos, height, width) +
             + getBottomRightNeighbor(field, pos, height, width) +
             + getBottomNeighbor(field, pos, height, width) +
             + getBottomLeftNeighbor(field, pos, height, width) +
             + getLeftNeighbor(field, pos, height, width) +
             + getUpperLeftNeighbor(field, pos, height, width);
    }
}

Field::Field(Galaxy& galaxy) {
    curField = galaxy.getField();
    nextField = curField;
    this->size = galaxy.getSize();
}

Field::~Field() {
}

int Field::getSize() {
    return this->size;
}

void Field::update(Galaxy& galaxy) {
    int numNeighbors = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            int pos = i * size + j;
            numNeighbors = getNumNeighbors(curField, pos, size, size);
            bool keepAlive = isSurvived(numNeighbors, galaxy.getRules().survival()) && isAlive(curField[pos]);
            bool becameAlive = !isAlive(curField[pos]) && isBorn(numNeighbors, galaxy.getRules().birth());
            nextField[pos] = (keepAlive || becameAlive );
        }
    }
    std::swap(curField, nextField);
}

bool Field::getCell(int i, int j) const {
    return curField[i * size + j];
}
