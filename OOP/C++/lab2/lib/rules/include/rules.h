#pragma once
#include <string>
#include <map>

class Rules {
public:
    void setBirthRules(std::string line);
    void setSurvivalRules(std::string line);
    const std::map<int, char>& birth() const;
    const std::map<int, char>& survival() const;
    std::string output();
private:
    std::map<int, char> birthRules;
    std::map<int, char> survivalRules;
};
