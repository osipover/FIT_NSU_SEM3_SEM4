#include "rules.h"

std::map<int, char> convertStrToMap(std::string line) {
    std::map<int, char> map;
    for (int i = 0; i < line.size(); ++i) {
        map.insert(std::pair<int, int>(line[i] - '0', line[i]));
    }
    return map;
}

void Rules::setBirthRules(std::string line) {
    this->birthRules = convertStrToMap(line);
}
void Rules::setSurvivalRules(std::string line) {
    this->survivalRules = convertStrToMap(line);
}

const std::map<int, char>& Rules::birth() const {
    return this->birthRules;
}

const std::map<int, char>& Rules::survival() const {
    return this->survivalRules;
}

std::string Rules::output() {
    std::string line = "B";
    for (auto it = this->birthRules.begin(); it != this->birthRules.end(); ++it) {
        line += it->second;
    }
    line += "/S";
    for (auto it = this->survivalRules.begin(); it != this->survivalRules.end(); ++it) {
        line += it->second;
    }
    return line;
}
