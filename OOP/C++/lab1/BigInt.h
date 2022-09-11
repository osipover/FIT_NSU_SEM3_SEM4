#ifndef LAB1_BIGINT_H
#define LAB1_BIGINT_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class BigInt{
private:
    vector<int> num;
    vector<int> zeroCount;
    bool sign;
public:
    BigInt();
    BigInt(int);
    BigInt(string);
    ~BigInt();

    BigInt& operator=(const BigInt&);

    BigInt operator~() const;

    BigInt& operator++();
    void Print();
};

#endif //LAB1_BIGINT_H
