#include <iostream>
#include "life.h"

static int getNumNeighbors(int* field, int pos, int height, int width);
static bool isSurvived(int numNeighbors, const std::map<int, int>& survivalRules);
static bool isBorn(int numNeighbors, const std::map<int, int>& birthRules);
static bool isAlive(int cell);

Field::Field(int height, int width) {
    this->height = height;
    this->width = width;
    curField = new int[height * width];
    nextField = new int[height * width];
}

Field::~Field() {
    delete[] curField;
    delete[] nextField;
}

int Field::getHeight() {
    return height;
}

int Field::getWidth() {
    return width;
}

void Field::init() { 
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            curField[i * height + j] = 0;
            nextField[i * height + j] = 0;
        }
    }
    curField[0 * height + 2] = 1;
    curField[1 * height + 2] = 1;
    curField[1 * height + 0] = 1;
    curField[2 * height + 2] = 1;
    curField[2 * height + 1] = 1;
}

void Field::update(Galaxy& galaxy) {
    const std::map<int, int>& birthRules = galaxy.getBirthRules();
    const std::map<int, int>& survivalRules = galaxy.getSurvivalRules();
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int pos = i * height + j;
            nextField[pos] = getNumNeighbors(curField, pos, height, width);
            bool keepAlive = isSurvived(nextField[pos], survivalRules) && isAlive(curField[pos]);
            bool becameAlive = !isAlive(curField[pos]) && isBorn(nextField[pos], birthRules);
            nextField[pos] = (keepAlive || becameAlive ? 1 : 0);
        }
    }
    std::swap(curField, nextField);
}

void Field::output() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            std::cout << (curField[i * height + j] == 1 ? "# " : ". ");
        }
        std::cout << std::endl;
    }
}

bool isSurvived(int numNeighbors, const std::map<int, int>& survivalRules) {
    for (auto it = survivalRules.begin(); it != survivalRules.end(); ++it) {
        if (numNeighbors < it->first) return false;
        if (numNeighbors == it->first) return true;
    }
    return false;
}

bool isBorn(int numNeighbors, const std::map<int, int>& birthRules) {
    for (auto it = birthRules.begin(); it != birthRules.end(); ++it) {
        if (numNeighbors < it->first) return false;
        if (numNeighbors == it->first) return true;
    }
    return false;
}

bool isAlive(int cell) {
    if (cell == 1) return true;
    else return false;
}

int getUpperNeighbor(int* field, int pos, int height, int width) {
    if (pos < width) {
        return field[height * width - width + pos];
    }
    else {
        return field[pos - width];
    }
}

int getUpperRightNeighbor(int* field, int pos, int height, int width) {
    if ((pos < width) || ((pos + 1) % width == 0)) {
        return 0;
    }
    else {
        return field[pos - width + 1];
    }
}

int getRightNeighbor(int* field, int pos, int height, int width) {
    if ((pos + 1) % width == 0) {
        return field[pos - width + 1];
    }
    else {
        return field[pos + 1];
    }
}

int getBottomRightNeighbor(int* field, int pos, int height, int width) {
    if (((pos + 1) % width == 0) || (pos >= (height * width - width))) {
        return 0;
    }
    else {
        return field[pos + width + 1];
    }
}

int getBottomNeighbor(int* field, int pos, int height, int width) {
    if (pos >= (height * width - width)) {
        return field[(pos + width) % (width * height)];
    }
    else {
        return field[pos + width];
    }
}

int getBottomLeftNeighbor(int* field, int pos, int height, int width) {
    if ((pos % width == 0) || (pos >= (height * width - width))) {
        return 0;
    }
    else {
        return field[pos + width - 1];
    }
}

int getLeftNeighbor(int* field, int pos, int height, int width) {
    if (pos % width == 0) {
        return field[pos + width - 1];
    }
    else {
        return field[pos - 1];
    }
}

int getUpperLeftNeighbor(int* field, int pos, int height, int width) {
    if ((pos % width == 0) || (pos < width)) {
        return 0;
    }
    else {
        return field[pos - width - 1];
    }
}

int getNumNeighbors(int* field, int pos, int height, int width) {
    return getUpperNeighbor(field, pos, height, width) +
         + getUpperRightNeighbor(field, pos, height, width) +
         + getRightNeighbor(field, pos, height, width) +
         + getBottomRightNeighbor(field, pos, height, width) +
         + getBottomNeighbor(field, pos, height, width) +
         + getBottomLeftNeighbor(field, pos, height, width) +
         + getLeftNeighbor(field, pos, height, width) +
         + getUpperLeftNeighbor(field, pos, height, width);
}
