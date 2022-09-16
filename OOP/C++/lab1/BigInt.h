#ifndef LAB1_BIGINT_H
#define LAB1_BIGINT_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class BigInt{
private:
    vector<int> data;
    bool sign;
public:
    BigInt();
    BigInt(int);
    BigInt(string);

    BigInt& operator=(const BigInt&);
    BigInt& operator++();
    BigInt operator++(int);
    BigInt& operator--();
    BigInt operator--(int);
    BigInt operator~() const;

    bool operator==(const BigInt&) const;
    bool operator!=(const BigInt&) const;
    bool operator<(const BigInt&) const;
    bool operator>(const BigInt&) const;
    bool operator<=(const BigInt&) const;
    bool operator>=(const BigInt&) const;

    void Print();
};

#endif //LAB1_BIGINT_H
