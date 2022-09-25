#include <list>
#include <fstream>
#include <string>
using namespace std;

typedef struct TStream{
	ifstream input;
	ofstream output;
}TStream;

TStream* OpenStream(const string& inputFile, const string& outputFile);
void CloseStream(TStream* stream);

typedef struct TWord {
	string word;
	int count;
} TWord;

class WordTable {
public:
	WordTable(ifstream& input);
	void AddWord(const string& word);
	void Output(ofstream& output);
	void Sort();
    	~WordTable();
private:
    	list<TWord*> table;
	int countWords;
};
