#include "interface.h"

int calcProcent(int num, int total) {
    float prop = (float) num / (float) total;
    int procent = (int) (prop * 100);
    return procent;
}

Output::Output(const string &fileName){
    stream.open(fileName);
}

void Output::outputData(WordTable& table){
    auto sortedTable = table.getSortedTable();
    for (auto it = sortedTable.rbegin(); it != sortedTable.rend(); ++it){
        stream << *(it->second) << ';';
        stream << it->first << ';';
        stream << calcProcent(it->first, table.getCountWords())  << '%' << endl;
    }
}

