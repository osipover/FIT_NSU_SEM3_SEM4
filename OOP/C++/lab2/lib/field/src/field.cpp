#include <iostream>
#include <algorithm>
#include <regex>
#include "life.h"

static int getNumNeighbors(const std::vector<bool>& field, int pos, int height, int width);
static bool isSurvived(int numNeighbors, const std::map<int, char>& survivalRules);
static bool isBorn(int numNeighbors, const std::map<int, char>& birthRules);
static bool isAlive(bool cell);

Field::Field(Galaxy& galaxy) {
    curField = galaxy.getField();
    nextField = curField;
    this->height = galaxy.getHeight();
    this->width = galaxy.getWidth();
}

Field::~Field() {
}

int Field::getHeight() {
    return height;
}

int Field::getWidth() {
    return width;
}

void Field::update(Galaxy& galaxy) {
    int numNeighbors = 0;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int pos = i * width + j;
            numNeighbors = getNumNeighbors(curField, pos, height, width);
            bool keepAlive = isSurvived(numNeighbors, galaxy.getRules().survival()) && isAlive(curField[pos]);
            bool becameAlive = !isAlive(curField[pos]) && isBorn(numNeighbors, galaxy.getRules().birth());
            nextField[pos] = (keepAlive || becameAlive );
        }
    }
    std::swap(curField, nextField);
}

void Field::output() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            std::cout << (curField[i * width + j] == true ? "# " : ". ");
        }
        std::cout << std::endl;
    }
}

void Field::output(std::ofstream& output) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (curField[i * width + j] == true) {
                output << i << " " << j << std::endl;
            }
        }
    }
}

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
