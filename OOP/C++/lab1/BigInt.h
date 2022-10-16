#ifndef LAB1_BIGINT_H
#define LAB1_BIGINT_H

#include <iostream>
#include <string>
#include <vector>
enum {BASE = 1000000000};
using namespace std;

class BigInt{
public:
    BigInt();
    explicit BigInt(int);
    explicit BigInt(string);

    BigInt operator~() const;

    BigInt& operator=(const BigInt&);

    BigInt operator+() const;
    BigInt operator-() const;

    BigInt& operator++();
    BigInt operator++(int);
    BigInt& operator--();
    BigInt operator--(int);

    BigInt& operator+=(const BigInt&);
    BigInt& operator-=(const BigInt&);
    BigInt& operator*=(const BigInt&);
    BigInt& operator/=(const BigInt&);
    BigInt& operator%=(const BigInt&);

    BigInt& operator&=(const BigInt&);
    BigInt& operator|=(const BigInt&);
    BigInt& operator^=(const BigInt&);

    bool operator==(const BigInt&) const;
    bool operator!=(const BigInt&) const;
    bool operator<(const BigInt&) const;
    bool operator>(const BigInt&) const;
    bool operator<=(const BigInt&) const;
    bool operator>=(const BigInt&) const;

    explicit operator int() const;
    explicit operator string() const;

    size_t size() const;

    friend ostream& operator<<(ostream&, const BigInt&);

    bool operator>(const int&) const;
    BigInt& operator+=(const int&);
    BigInt& operator/=(const int&);
private:
    vector<int> data;
    bool sign;
    bool isZero(const BigInt&);
};

BigInt absBigInt(const BigInt&);

BigInt operator+(const BigInt& left, const BigInt& right);
BigInt operator-(const BigInt& left, const BigInt& right);
BigInt operator*(const BigInt& left, const BigInt& right);
BigInt operator/(const BigInt& left, const BigInt& right);
BigInt operator%(const BigInt& left, const BigInt& right);

BigInt operator&(const BigInt& left, const BigInt& right);
BigInt operator|(const BigInt& left, const BigInt& right);
BigInt operator^(const BigInt& left, const BigInt& right);

ostream& operator<<(ostream&, const BigInt&);

BigInt operator*(const BigInt& left, const int& right);
BigInt operator%(const BigInt& left, const int&);
#endif //LAB1_BIGINT_H
