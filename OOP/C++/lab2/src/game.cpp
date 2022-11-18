#include "life.h"
#include "commands.h"

void GameControler::start(Field& field, Galaxy& galaxy) {
    std::map<std::string, ICommand*> commandList = createCommandList();
    while (true) {
        std::string line;
        std::getline(std::cin, line);

        std::vector<std::string> words = split(line, ' ');

        if (commandList.find(words[0]) != commandList.end()) {
            ICommand* command = commandList.find(words[0])->second;
            int res = command->execute(field, galaxy, words);
            if (res == 0) break;
        }
    }
}
