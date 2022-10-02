#ifndef LAB1_BIGINT_H
#define LAB1_BIGINT_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class BigInt{
public:
    BigInt();
    explicit BigInt(int);
    explicit BigInt(string);

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
    friend BigInt operator*(const BigInt& left, const BigInt& right);
    //friend BigInt operator/(const BigInt& left, const BigInt& right);

    explicit operator int() const;
    explicit operator string() const;

    size_t size() const;

    friend ostream& operator<<(ostream&, const BigInt&);
private:
    const int base = 1000000000;
    vector<int> data;
    bool sign;
};

BigInt operator+(BigInt left, const BigInt& right);
BigInt operator-(BigInt left, const BigInt& right);
BigInt operator*(const BigInt& left, const BigInt& right);
//BigInt operator/(const BigInt& left, const BigInt& right);

ostream& operator<<(ostream&, const BigInt&);
#endif //LAB1_BIGINT_H
