#include <sstream>
#include <iostream>
#include <thread>
#include <chrono>
#include <regex>
#include "commands.h"
#include "field.h"
#include "galaxy.h"

std::vector<std::string> split(const std::string& line, char dev) {
    std::vector<std::string> args;
    std::stringstream stream;
    stream.str(line);
    std::string item;
    while (std::getline(stream, item, dev)) {
        args.push_back(item);
    }
    return args;
}

static int convertStrToInt(std::string line) {
    int value = 0, pow = 1;
    for (int i = line.length() - 1; i >= 0; --i) {
        value = pow * (line[i] - '0') + value;
        pow *= 10;
    }
    return value;
}

std::map<std::string, std::unique_ptr<ICommand>> createCommandList() {
    std::map<std::string, std::unique_ptr<ICommand>> commandList;

    auto creator = std::unique_ptr<ICommandCreator>{ new ExitCreator };
    commandList.insert(std::pair<std::string, std::unique_ptr<ICommand>>("exit", creator->create()));

    creator = std::unique_ptr<ICommandCreator>{ new HelpCreator };
    commandList.insert(std::pair<std::string, std::unique_ptr<ICommand>>("help", creator->create()));

    creator = std::unique_ptr<ICommandCreator>{ new TickCreator };
    commandList.insert(std::pair<std::string, std::unique_ptr<ICommand>>("tick", creator->create()));

    creator = std::unique_ptr<ICommandCreator>{ new PlayCreator };
    commandList.insert(std::pair<std::string, std::unique_ptr<ICommand>>("play", creator->create()));

    creator = std::unique_ptr<ICommandCreator>{ new DumpCreator };
    commandList.insert(std::pair<std::string, std::unique_ptr<ICommand>>("dump", creator->create()));

    return commandList;
}

int Exit::execute(Field& field, Galaxy& galaxy, std::vector<std::string> args) {
    return 0;
}

int Help::execute(Field& field, Galaxy& galaxy, std::vector<std::string> args) {
    std::cout << std::endl;
    std::cout << "dump <filename> -- to consrerv the universe in a file\n\n";
    std::cout << "tick <n> -- to calculate n iterations and output result\n\n";
    std::cout << "exit -- to finish the game\n\n";
    
    return 1;
}

int Tick::execute(Field& field, Galaxy& galaxy, std::vector<std::string> args) {
    int numIterat = convertStrToInt(args[1]);
    while (numIterat > 0) {
        field.update(galaxy);
        numIterat--;
    }
    field.output();

    return 2;
}

int Play::execute(Field& field, Galaxy& galaxy, std::vector<std::string> args) {
    int numIterat = convertStrToInt(args[1]);        
    while (numIterat > 0) {
        system("cls");        
        field.update(galaxy);
        field.output();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        numIterat--;
    }

    return 3;
}

int Dump::execute(Field& field, Galaxy& galaxy, std::vector<std::string> args) {
    std::ofstream output;
    std::cmatch result;
    std::regex reg("[\\w]+.txt$");
    if (std::regex_match(args[1].c_str(), result, reg)) {
        output.open(args[1]);
        if (output.is_open()) {
            output << "#Life 1.06\n";
            output << "#N " << galaxy.getName() << std::endl;
            output << "#R " << galaxy.getRules().output() << std::endl;
            output << "#S " << "H" << galaxy.getHeight() << "/W" << galaxy.getWidth() << std::endl;
            field.output(output);
        }
        throw CommandExceptions("I can't open this file. Try again.");
    }
    else {
        throw CommandExceptions("File has to be with \"txt\" format. Try again.");
    }
    output.close();

    return 4;
}
