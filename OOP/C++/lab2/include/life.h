#ifndef LAB2_LIFE_H
#define LAB2_LIFE_H
#include <fstream>
#include <map>

class Stream {
public:
    Stream(int argc, char** argv);
    void openInFile(const std::string& fileName);
    void openOutFile(const std::string& fileName);
    void close();
    std::ifstream& getInFile();
private:
    std::ifstream input;
    std::ofstream output;
    int numIterat;
};

class Galaxy {
public:
    Galaxy();
    void parc(std::ifstream& input);
    std::string getName();
    const std::map<int, int>& getBirthRules() const;
    const std::map<int, int>& getSurvivalRules() const;
private:
    std::string name;
    int height;
    int width;
    std::map<int, int> birthRules;
    std::map<int, int> survivalRules;
    void parcGalaxyName(std::string& line, std::ifstream& input);
    void parcRules(std::string& line, std::ifstream& input);
    void parcFieldSize(std::string& line, std::ifstream& input);
};

class Field {
public:
    Field() : height(0), width(0), curField(nullptr), nextField(nullptr) {}
    Field(int height, int width);
    ~Field();
    int getHeight();
    int getWidth();
    void init();
    void update(Galaxy& galaxy);
    void output();
private:
    int height;
    int width;
    int* curField;
    int* nextField;
};

class GameControler {
private:
public:
    void start() {
    }
};

#endif //LAB2_LIFE_H
