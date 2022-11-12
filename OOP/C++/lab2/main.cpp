#include <iostream>
#include <thread>
#include <chrono>
#include "life.h"

int main(int argc, char* argv[]) {
    Stream stream(argc, argv);
    Galaxy galaxy;
    galaxy.parc(stream.getInFile());
    /*
    Galaxy galaxy;
    Field field(10, 10);
    field.init();
    while (true) {        
        field.output();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        system("cls");
        field.update(galaxy);
    }
    */
    return 0;
    
}
