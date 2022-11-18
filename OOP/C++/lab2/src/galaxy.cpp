#include "life.h"
#include <string>
#include <vector>
#include <iostream>
#include <regex>

Galaxy::Galaxy():name("Life"), height(100), width(100) {

}

Galaxy::Galaxy(std::ifstream& input) {
    parc(input);
}

std::map<int, int> convertStrToMap(std::string line) {
    std::map<int, int> map;
    for (int i = 0; i < line.size(); ++i) {
        map.insert(std::pair<int, int>(line[i] - '0', line[i] - '0'));
    }
    return map;
}

int convertStrToInt(std::string line) {
    int value = 0, pow = 1;
    for (int i = line.length() - 1; i >= 0; --i) {
        value = pow * (line[i] - '0') + value;
        pow *= 10;
    }
    return value;
}

void Galaxy::parcGalaxyName(std::string& line, std::ifstream& input) {
    std::cmatch result;
    std::regex reg("(#N)( )([\\w]+)");
    if (std::regex_match(line.c_str(), result, reg)) {
        name = result[3];
        std::getline(input, line);
    }
    else {
        name = "Unknown";
    }
}

void Galaxy::parcRules(std::string& line, std::ifstream& input) {
    std::cmatch result;
    std::regex reg("(#R)( )(B)([0-8]+)(/)(S)([0-8]+)");
    if (std::regex_match(line.c_str(), result, reg)) {
        birthRules = convertStrToMap(result[4]);
        survivalRules = convertStrToMap(result[7]);
        std::getline(input, line);
    }
    else {
        birthRules = convertStrToMap("3");
        survivalRules = convertStrToMap("23");
    }
}

void Galaxy::parcFieldSize(std::string& line, std::ifstream& input) {
    std::cmatch result;
    std::regex reg("(#S)( )(M)([0-8]+)(/)(N)([0-8]+)");
    if (std::regex_match(line.c_str(), result, reg)) {
        this->height = convertStrToInt(result[4]);
        this->width = convertStrToInt(result[7]);
    }
    else {
        this->height = 10;
        this->width = 10;
    }
}

std::vector<int> Galaxy::parcCells(std::string& line, std::ifstream& input) {
    std::vector<int> field(height * width, 0);

    std::cmatch result;
    std::regex reg("([0-9]+)( )([0-9]+)");
    while (std::getline(input, line)) {
        if (std::regex_match(line.c_str(), result, reg)) {
            field[convertStrToInt(result[1]) * width + convertStrToInt(result[3])] = 1;
        }
    }
    return field;
}

void Galaxy::parc(std::ifstream& input) {
    std::string line;
    std::getline(input, line);
    if (line != "#Life 1.06") {
        throw std::invalid_argument("invalid format for input file");
    }
    std::getline(input, line);
    parcGalaxyName(line, input);
    parcRules(line, input);
    parcFieldSize(line, input);
    field = parcCells(line, input);
}

std::vector<int>& Galaxy::getField() {
    return this->field;
}
int Galaxy::getHeight() {
    return this->height;
}

int Galaxy::getWidth() {
    return this->width;
}

std::string Galaxy::getName() {
    return name;
}
const std::map<int, int>& Galaxy::getBirthRules() const {
    return birthRules;
}
const std::map<int, int>& Galaxy::getSurvivalRules() const {
    return survivalRules;
}
