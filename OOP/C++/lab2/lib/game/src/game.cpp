#include <iostream>
#include "field.h"
#include "galaxy.h"
#include "commands.h"

void Game::start(Field& field, Galaxy& galaxy) {
    std::map<std::string, std::unique_ptr<ICommand>> commandList = createCommandList();
    while (true) {
        std::string line;
        std::getline(std::cin, line);
        std::vector<std::string> args = split(line, ' ');

        auto it = commandList.find(args[0]);
        if (it != commandList.end()) {
            ICommand* command = it->second.get();
            try {
                int res = command->execute(field, galaxy, args);
                if (res == 0) break;
            }
            catch (CommandExceptions& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else {
            std::cout << "I don't know this command.\nType \"help\" to get commands list.\n";
        }
    }
}
