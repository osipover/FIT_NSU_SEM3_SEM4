#include <sstream>
#include <iostream>
#include <thread>
#include <chrono>
#include <regex>
#include "commands.h"

static int convertStrToInt(std::string line) {
    int value = 0, pow = 1;
    for (int i = line.length() - 1; i >= 0; --i) {
        value = pow * (line[i] - '0') + value;
        pow *= 10;
    }
    return value;
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

void Tick::outputField(Field& field) {
    for (int i = 0; i < field.getSize(); ++i) {
        for (int j = 0; j < field.getSize(); ++j) {
            std::cout << (field.getCell(i, j) == true ? "# " : ". ");
        }
        std::cout << std::endl;
    }
}

int Tick::execute(Field& field, Galaxy& galaxy, std::vector<std::string> args) {
    int numIterat = convertStrToInt(args[1]);
    while (numIterat > 0) {
        field.update(galaxy);
        numIterat--;
    }
    outputField(field);

    return 2;
}

void Play::outputField(Field& field) {
    for (int i = 0; i < field.getSize(); ++i) {
        for (int j = 0; j < field.getSize(); ++j) {
            std::cout << (field.getCell(i, j) == true ? "# " : ". ");
        }
        std::cout << std::endl;
    }
}

int Play::execute(Field& field, Galaxy& galaxy, std::vector<std::string> args) {
    int numIterat = convertStrToInt(args[1]);        
    while (numIterat > 0) {
        system("cls");        
        field.update(galaxy);
        outputField(field);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        numIterat--;
    }

    return 3;
}

void Dump::outputField(std::ofstream& output, Field& field) {
    for (int i = 0; i < field.getSize(); ++i) {
        for (int j = 0; j < field.getSize(); ++j) {
            if (field.getCell(i, j) == true) {
                output << i << " " << j << std::endl;
            }
        }
    }
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
            output << "#S " << galaxy.getSize() << std::endl;
            outputField(output, field);
        }
        else 
            throw CommandExceptions("I can't open this file. Try again.");
    }
    else {
        throw CommandExceptions("File has to be with \"txt\" format. Try again.");
    }
    output.close();

    return 4;
}
