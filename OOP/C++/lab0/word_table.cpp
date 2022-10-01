#include "interface.h"
using namespace std;

bool IsLetter(char symb) {
    if ((('a' <= symb) && (symb <= 'z')) || (('A' <= symb) && (symb <= 'Z')))
        return true;
    else
        return false;
}

bool CompareTwoWords(const string& word1, const string& word2) {
    if (word1 == word2) return true;
    else return false;
}

pair<int, string> GetPairWithMaxCount(map<string, int> &table) {
    auto cur = table.begin();
    for (auto it = table.begin(); it != table.end(); ++it) {
        if (cur->second < it->second) cur = it;
    }
    pair<int, string> maxPair(cur->second, cur->first);
    table.erase(cur->first);
    return maxPair;
}

multimap<int, string> SortTable(map<string, int> &table){
    multimap<int, string> sortedTable;
    while (!table.empty()){
        auto cur = GetPairWithMaxCount(table);
        sortedTable.insert(cur);
    }
    return sortedTable;
}

WordTable::WordTable(const string& fileName) : countWords(0){
    ifstream input;
    input.open(fileName);
    string word;
    char symb = '0';
    input.get(symb);
    while (!input.eof()) {
        while ((IsLetter(symb)) && (!input.eof())) {
            word += symb;
            input.get(symb);
        }
        if (!word.empty()) {
            AddWord(word);
            word = "";
        }
        input.get(symb);
    }
    sortedTable = SortTable(table);
}

void WordTable::AddWord(const string& word) {
    for (auto it = table.begin(); it != table.end(); ++it) {
        if (CompareTwoWords(it->first, word)) {
            it->second++;
            countWords++;
            return;
        }
    }
    table.insert(make_pair(word, 1));
    countWords++;
}
