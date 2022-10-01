#include <map>
#include <fstream>
#include <string>
using namespace std;

class Output;

class WordTable {
public:
    explicit WordTable(const string& fileName);
    void AddWord(const string& word);
    friend class Output;
private:
    map<string,int> table;
    multimap<int, string> sortedTable;
    int countWords;
};

class Output {
public:
    explicit Output(const string &fileName);
    void OutputData(const WordTable& wordTable);
private:
    ofstream stream;
};
