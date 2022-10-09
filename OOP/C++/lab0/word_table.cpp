#include "interface.h"
#include <iostream>
using namespace std;

bool isLetter(char symb) {
    if ((('a' <= symb) && (symb <= 'z')) || (('A' <= symb) && (symb <= 'Z')))
        return true;
    else
        return false;
}

bool compareTwoWords(const string& word1, const string& word2) {
    if (word1 == word2) return true;
    else return false;
}

multimap<int, const string*> sortTable(const map<string, int> &table){
    multimap<int, const string*> sortedTable;
    for (auto it = table.begin(); it != table.end(); ++it){
        sortedTable.insert(pair<int, const string*>(it->second, &(it->first)));
    }
    return sortedTable;
}

void WordTable::addWord(const string& word) {
    for (auto it = table.begin(); it != table.end(); ++it) {
        if (compareTwoWords(it->first, word)) {
            it->second++;
            countWords++;
            return;
        }
    }
    table.insert(make_pair(word, 1));
    countWords++;
}

WordTable::WordTable(const string& fileName) : countWords(0){
    ifstream input;
    input.open(fileName);
    string word;
    char symb = '0';
    input.get(symb);
    while (!input.eof()) {
        while ((isLetter(symb)) && (!input.eof())) {
            word += symb;
            input.get(symb);
        }
        if (!word.empty()) {
            addWord(word);
            word = "";
        }
        input.get(symb);
    }
    sortedTable = sortTable(table);
}



multimap<int, const string*>& WordTable:: getSortedTable(){
    return sortedTable;
}

int WordTable::getCountWords() {
    return countWords;
}
