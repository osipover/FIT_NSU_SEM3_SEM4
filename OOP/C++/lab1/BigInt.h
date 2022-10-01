#ifndef LAB1_BIGINT_H
#define LAB1_BIGINT_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class BigInt{
public:
    BigInt();
    BigInt(int);
    BigInt(string);

    BigInt operator+() const;
    BigInt operator-() const;

    BigInt& operator=(const BigInt&);
    BigInt& operator++();
    BigInt operator++(int);
    BigInt& operator--();
    BigInt operator--(int);
    BigInt operator~() const;

    BigInt& operator+=(const BigInt&);
    BigInt& operator-=(const BigInt&);

    bool operator==(const BigInt&) const;
    bool operator!=(const BigInt&) const;
    bool operator<(const BigInt&) const;
    bool operator>(const BigInt&) const;
    bool operator<=(const BigInt&) const;
    bool operator>=(const BigInt&) const;

    friend BigInt operator+(BigInt left, const BigInt& right);
    friend BigInt operator-(BigInt left, const BigInt& right);

    void Print();
private:
    const int base = 1000000000;
    vector<int> data;
    bool sign;
};

BigInt operator+(BigInt left, const BigInt& right);
BigInt operator-(BigInt left, const BigInt& right);

#endif //LAB1_BIGINT_H
