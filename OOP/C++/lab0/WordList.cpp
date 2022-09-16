#include <algorithm>
#include "WordList.h"
using namespace std;

bool IsLetter(char symb) {
    if ((('a' <= symb) && (symb <= 'z')) || (('A' <= symb) && (symb <= 'Z')))
        return true;
    else
        return false;
}

bool comp(TWord* first, TWord* second) {
    return first->count > second->count;
}

bool CompareTwoWords(string word1, string word2){
    if (word1 == word2)
        return true;
    if (word1[0] < word2[0])
        word1[0] += ' ';
    else
        word2[0] += ' ';
    if (word1 == word2)
        return true;
    return false;
}

void WordList::AddWord(string word) {
    for (int i = 0; i < list.size(); ++i) {
        if (CompareTwoWords(list.at(i)->word, word)) {
            list.at(i)->count++;
            countWords++;
            return;
        }
    }
    TWord* item = new TWord;
    item->count = 1;
    item->word = word;
    list.push_back(item);
    countWords++;
}

WordList::WordList(ifstream& file) {
    countWords = 0;
    string word = "";
    char symb;
    file.get(symb);
    while (!file.eof()) {
        while ((IsLetter(symb)) && (!file.eof())) {
            word = word + symb;
            file.get(symb);
        }
        if (word != "") {
            AddWord(word);
            word = "";
        }
        file.get(symb);
    }
}

WordList::~WordList() {
    for (int i = 0; i < list.size(); ++i)
        delete list.at(i);
}

void WordList::Sort() {
    sort(list.begin(), list.end(), comp);
}

int CalcProcent(int num, int total){
    float prop = (float)num/(float)total;
    int procent = (int)(prop*100);
    return procent;
}

void WordList::Print() {
    for (int i = 0; i < list.size(); ++i){
        cout << list.at(i)->word << " ";
        cout << list.at(i)->count << " ";
        cout << CalcProcent(list.at(i)->count, countWords) << "%" << endl;
    }
}
