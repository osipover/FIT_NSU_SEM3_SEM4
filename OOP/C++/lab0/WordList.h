#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

typedef struct TWord {
	string word;
	int count;
} TWord;

class WordList {
private:
	vector<TWord*> list;
    int countWords;
public:
	WordList(ifstream& file);
	~WordList();
	void AddWord(string word);
	void Print();
	void Sort();
};
