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

    friend BigInt operator*(const BigInt& left, const int& right);
    friend BigInt operator/(const BigInt& left, const BigInt& right);
    friend BigInt operator%(const BigInt& left, const BigInt& right);


    friend BigInt operator&(const BigInt& left, const BigInt& right);
    friend BigInt operator|(const BigInt& left, const BigInt& right);
    friend BigInt operator^(const BigInt& left, const BigInt& right);

    explicit operator int() const;
    explicit operator string() const;

    size_t size() const;

    friend ostream& operator<<(ostream&, const BigInt&);

    bool operator>(const int&) const;
    BigInt& operator+=(const int&);
    BigInt& operator/=(const int&);
    friend BigInt operator%(const BigInt& left, const int&);
private:
    vector<int> data;
    bool sign;
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
