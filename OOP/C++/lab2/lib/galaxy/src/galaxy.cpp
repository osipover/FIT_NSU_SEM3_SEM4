#include <iostream>
#include <regex>
#include "life.h"
#include <fstream>

namespace {
    int convertStrToInt(std::string line) {
        int value = 0, pow = 1;
        for (int i = line.length() - 1; i >= 0; --i) {
            value = pow * (line[i] - '0') + value;
            pow *= 10;
        }
        return value;
    }

    std::string parcGalaxyName(std::string& line, std::ifstream& input) {
        std::string name;
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
        return name;
    }

    Rules* parcRules(std::string& line, std::ifstream& input) {
        Rules* rules = new Rules;
        std::cmatch result;
        std::regex reg("(#R)( )(B)([0-8]+)(/)(S)([0-8]+)");
        if (std::regex_match(line.c_str(), result, reg)) {
            rules->setBirthRules(result[4]);
            rules->setSurvivalRules(result[7]);
            std::getline(input, line);
        }
        else {
            std::cout << "[WARRNING] No rules of the galaxy. The game will start with B2/S23\n" << std::endl;
            rules->setBirthRules("3");
            rules->setSurvivalRules("23");
        }
        return rules;
    }

    int parcFieldSize(std::string& line, std::ifstream& input) {
        int fieldSize = 0;
        std::cmatch result;
        std::regex reg("(#S)( )([0-9]+)");
        if (std::regex_match(line.c_str(), result, reg)) {
            fieldSize = convertStrToInt(result[3]);
        }
        else {
            std::cout << "[WARRNING] No size of the field." << std::endl;
            fieldSize = 10;
        }
        return fieldSize;
    }

    std::vector<bool> parcCells(std::string& line, std::ifstream& input, int size) {
        std::vector<bool> field(size*size, false);

        std::cmatch result;
        std::regex reg("([0-9]+)( )([0-9]+)");
        bool isFieldEmpty = true;
        while (std::getline(input, line)) {
            if (std::regex_match(line.c_str(), result, reg)) {
                if ((convertStrToInt(result[1]) < size) && (convertStrToInt(result[3]) < size)) {
                    field[convertStrToInt(result[1]) * size + convertStrToInt(result[3])] = true;
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
}

Rules& Galaxy::getRules() {
    return *(this->rules);
}

std::vector<bool>& Galaxy::getField() {
    return this->field;
}

int Galaxy::getSize() {
    return this->size;
}

std::string Galaxy::getName() {
    return name;
}

void operator >> (std::ifstream& input, Galaxy& galaxy) {
    std::string line;
    std::getline(input, line);
    if (line != "#Life 1.06") {
        std::cout << "[ERROR] Input file has to be in #Life 1.06 format.";
    }
    std::getline(input, line);
    galaxy.name = parcGalaxyName(line, input);
    galaxy.rules = parcRules(line, input);
    galaxy.size = parcFieldSize(line, input);
    galaxy.field = parcCells(line, input, galaxy.size);
}
