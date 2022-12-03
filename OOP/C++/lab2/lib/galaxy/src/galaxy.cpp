#include <iostream>
#include <regex>
#include <fstream>
#include "galaxy.h"

Rules& Galaxy::getRules() {
    return this->rules;
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
        std::cout << "[WARRNING] No name of the galaxy." << std::endl;
        name = "Unknown";
    }
}

void Galaxy::parcRules(std::string& line, std::ifstream& input) {
    std::cmatch result;
    std::regex reg("(#R)( )(B)([0-8]+)(/)(S)([0-8]+)");
    if (std::regex_match(line.c_str(), result, reg)) {
        rules.setBirthRules(result[4]);
        rules.setSurvivalRules(result[7]);
        std::getline(input, line);
    }
    else {
        std::cout << "[WARRNING] No rules of the galaxy. The game will start with B2/S23\n" << std::endl;
        rules.setBirthRules("3");
        rules.setSurvivalRules("23");
    }
}

void Galaxy::parcFieldSize(std::string& line, std::ifstream& input) {
    std::cmatch result;
    std::regex reg("(#S)( )(H)([0-9]+)(/)(W)([0-9]+)");
    if (std::regex_match(line.c_str(), result, reg)) {
        this->height = convertStrToInt(result[4]);
        this->width = convertStrToInt(result[7]);
    }
    else {
        std::cout << "[WARRNING] No size of the field." << std::endl;
        this->height = 10;
        this->width = 10;
    }
}

std::vector<bool> Galaxy::parcCells(std::string& line, std::ifstream& input) {
    std::vector<bool> field(height * width, false);

    std::cmatch result;
    std::regex reg("([0-9]+)( )([0-9]+)");
    bool isFieldEmpty = true;
    while (std::getline(input, line)) {
        if (std::regex_match(line.c_str(), result, reg)) {
            if ((convertStrToInt(result[1]) < height) && (convertStrToInt(result[3]) < width)) {
                field[convertStrToInt(result[1]) * width + convertStrToInt(result[3])] = true;
                isFieldEmpty = false;
            }
            else
                std::cout << "[WARRNING] Cell (" << result[1] << "," << result[3] << ") is out of galaxy range.\n";
        }
    }
    if (isFieldEmpty) {
        std::cout << "[WARRNING] Field is empty.\n";
    }
    return field;
}

void operator >> (std::ifstream& input, Galaxy& galaxy) {
    std::string line;
    std::getline(input, line);
    if (line != "#Life 1.06") {
        std::cout << "[ERROR] Input file has to be in #Life 1.06 format.";
    }
    std::getline(input, line);
    
    galaxy.parcGalaxyName(line, input);
    galaxy.parcRules(line, input);
    galaxy.parcFieldSize(line, input);
    galaxy.field = galaxy.parcCells(line, input);
}

std::vector<bool>& Galaxy::getField() {
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
