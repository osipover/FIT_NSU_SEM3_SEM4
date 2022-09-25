#include <windows.h>
#include "WordTable.h"
using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    TStream* stream = OpenStream("input.txt", "output.csv");
    WordTable wordTable(stream->input);
    wordTable.Sort();
    wordTable.Output(stream->output);
    CloseStream(stream);
}
