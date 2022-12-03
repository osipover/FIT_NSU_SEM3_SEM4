#include <iostream>
#include <string>
#include "life.h"

int main(int argc, char* argv[]) {
    try {
        Pars pars;
        pars.commandLine(argc, argv);
        Galaxy galaxy;
        pars.getInput() >> galaxy;
        Field field(galaxy);
        Game game;
        game.start(field, galaxy);    
        return 0;
    }
    catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
        return 1;
    }
}
