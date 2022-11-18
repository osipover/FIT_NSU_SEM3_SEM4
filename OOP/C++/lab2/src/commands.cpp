#include <vector>
#include <string>
#include <sstream>
#include "commands.h"
#include <iostream>

std::vector<std::string> split(const std::string& line, char dev) {
    std::vector<std::string> words;
    std::stringstream stream;
    stream.str(line);
    std::string item;
    while (std::getline(stream, item, dev)) {
        words.push_back(item);
    }
    return words;
}

static int convertStrToInt(std::string line) {
    int value = 0, pow = 1;
    for (int i = line.length() - 1; i >= 0; --i) {
        value = pow * (line[i] - '0') + value;
        pow *= 10;
    }
    return value;
}

std::map<std::string, ICommand*> createCommandList() {
    std::map<std::string, ICommand*> commandList;

    ICommandCreator* creator = new ExitCreator;
    commandList.insert(std::pair<std::string, ICommand*>("exit", creator->create()));

    creator = new HelpCreator;
    commandList.insert(std::pair<std::string, ICommand*>("help", creator->create()));

    creator = new TickCreator;
    commandList.insert(std::pair<std::string, ICommand*>("tick", creator->create()));

    creator = new PlayCreator;
    commandList.insert(std::pair<std::string, ICommand*>("play", creator->create()));

    return commandList;
}

int Exit::execute(Field& field, Galaxy& galaxy, std::vector<std::string> words) {
    return 0;
}

int Help::execute(Field& field, Galaxy& galaxy, std::vector<std::string> words) {
    std::cout << std::endl;
    std::cout << "dump <filename> -- to consrerv the universe in a file\n\n";
    std::cout << "tick <n> -- to calculate n iterations and output result\n\n";
    std::cout << "exit -- to finish the game\n\n";
    
    return 1;
}

int Tick::execute(Field& field, Galaxy& galaxy, std::vector<std::string> words) {
    int numIterat = convertStrToInt(words[1]);
    while (numIterat > 0) {
        field.update(galaxy);
        numIterat--;
    }
    field.output();

    return 2;
}

int Play::execute(Field& field, Galaxy& galaxy, std::vector<std::string> words) {
    int numIterat = convertStrToInt(words[1]);        
    while (numIterat > 0) {
        system("cls");
        field.output();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        field.update(galaxy);
        numIterat--;
    }

    return 3;
}
