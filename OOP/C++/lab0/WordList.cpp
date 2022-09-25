#include <iostream>
#include <algorithm>
#include "WordTable.h"
using namespace std;

TStream* OpenStream(const string& inputFile, const string& outputFile){
    auto stream = new TStream;
    stream->input.open(inputFile);
    stream->output.open(outputFile);
    return stream;
}

void CloseStream(TStream* stream) {
    stream->input.close();
    stream->output.close();
    delete stream;
}

bool IsLetter(char symb) {
    if ((('a' <= symb) && (symb <= 'z')) || (('A' <= symb) && (symb <= 'Z')))
        return true;
    else
        return false;
}

bool comp(TWord *first, TWord *second) {
    return first->count > second->count;
}

bool CompareTwoWords(const string& word1, const string& word2) {
    if (word1 == word2) return true;
    else return false;
}

int CalcProcent(int num, int total) {
    float prop = (float) num / (float) total;
    int procent = (int) (prop * 100);
    return procent;
}

WordTable::WordTable(ifstream& input) : countWords(0){
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
}

void WordTable::AddWord(const string& word) {
    for (auto it = table.begin(); it != table.end(); ++it) {
        if (CompareTwoWords((*it)->word, word)) {
            (*it)->count++;
            countWords++;
            return;
        }
    }
    auto item = new TWord;
    item->count = 1;
    item->word = word;
    table.push_back(item);
    countWords++;
}

void WordTable::Sort() {
    table.sort(comp);
}

void WordTable::Output(ofstream& output) {
    for (auto it = table.begin(); it != table.end(); ++it){
        output << (*it)->word << ";";
        output << (*it)->count << ";";
        output << CalcProcent((*it)->count, countWords) << "%\n";
    }
}

WordTable::~WordTable() {
    for (auto it = table.begin(); it != table.end(); ++it)
        delete (*it);
}
