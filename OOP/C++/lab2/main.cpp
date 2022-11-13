#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include "life.h"

int main(int argc, char* argv[]) {
    Stream stream(argc, argv);
    Galaxy galaxy(stream.getInFile());
    Field field(galaxy);

    int numIterat = stream.getNumIterat();
    while (numIterat > 0) {
        field.output();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        system("cls");
        field.update(galaxy);
        numIterat--;
    }

    return 0;
}
