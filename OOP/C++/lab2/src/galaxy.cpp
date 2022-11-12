#include "life.h"
#include <string>
#include <vector>
#include <iostream>
#include <regex>

Galaxy::Galaxy():name("Life"), height(100), width(100) {
    
    //birthRules.insert(std::pair<int, int>(3, 3));
    //survivalRules.insert(std::pair<int, int>(2, 2));
    //survivalRules.insert(std::pair<int, int>(3, 3));
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
        std::getline(input, line);
    }
    else {
        this->height = 10;
        this->width = 10;
    }
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
}

//void Galaxy::parc(std::ifstream& input) {

//    std::cmatch result;
//
//    std::getline(input, line); 
//    std::regex reg("(#N)( )([\\w]+)");
//    if (std::regex_match(line.c_str(), result, reg)) {
//        this->name = result[3];
//    }
//
//    std::getline(input, line);
//    std::regex reg1("(#R)( )(B)([0-8]+)(/)(S)([0-8]+)");
//    if (std::regex_match(line.c_str(), result, reg1)) {
//        this->birthRules = convertStrToMap(result[4]);
//        this->survivalRules = convertStrToMap(result[7]);
//    }
//
//    std::getline(input, line);
//    std::regex reg2("(#S)( )(M)([0-8]+)(/)(N)([0-8]+)");
//    if (std::regex_match(line.c_str(), result, reg2)) {
//        this->height = convertStrToInt(result[4]);
//        this->width = convertStrToInt(result[7]);
//    }
//
//    
//}

std::string Galaxy::getName() {
    return name;
}
const std::map<int, int>& Galaxy::getBirthRules() const {
    return birthRules;
}
const std::map<int, int>& Galaxy::getSurvivalRules() const {
    return survivalRules;
}
