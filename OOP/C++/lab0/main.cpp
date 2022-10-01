#include <windows.h>
#include "interface.h"
using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    WordTable wordTable("input.txt");
    Output output("output.csv");
    output.OutputData(wordTable);
    return 0;
}
