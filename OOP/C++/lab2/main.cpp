#include <iostream>
#include <string>
#include "life.h"

int main(int argc, char* argv[]) {
    Stream stream(argc, argv);
    Galaxy galaxy(stream.getInFile());
    Field field(galaxy);

    GameControler game;
    game.start(field, galaxy);
    
    return 0;
}
