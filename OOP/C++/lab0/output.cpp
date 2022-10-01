#include "interface.h"

Output::Output(const string &fileName){
    stream.open(fileName);
}

int CalcProcent(int num, int total) {
    float prop = (float) num / (float) total;
    int procent = (int) (prop * 100);
    return procent;
}

void Output::OutputData(const WordTable& table){
    for (auto it = table.sortedTable.rbegin(); it != table.sortedTable.rend(); ++it){
        stream << it->second << ';';
        stream << it->first << ';';
        stream << CalcProcent(it->first, table.countWords) << endl;
    }
}
