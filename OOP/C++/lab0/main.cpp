#include <fstream>
#include "WordList.h"
using namespace std;

int main() {
    ifstream file;
    file.open("file.txt");
    WordList wordList(file);
    wordList.Sort();
    wordList.Print();
    file.close();
}
