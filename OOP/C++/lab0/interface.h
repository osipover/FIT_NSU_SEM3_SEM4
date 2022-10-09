#include <map>
#include <fstream>
#include <string>
using namespace std;

class WordTable {
public:
    explicit WordTable(const string& fileName);
    void addWord(const string& word);
    multimap<int, const string*>& getSortedTable();
    int getCountWords();
private:
    map<string,int> table;
    multimap<int, const string*> sortedTable;
    int countWords;
};

class Output {
public:
    explicit Output(const string &fileName);
    void outputData(WordTable& wordTable);
private:
    ofstream stream;
};
