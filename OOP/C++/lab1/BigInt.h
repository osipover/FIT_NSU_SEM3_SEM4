#ifndef LAB1_BIGINT_H
#define LAB1_BIGINT_H

#include <iostream>
#include <string>
#include <vector>
enum {BASE = 1000000000};

class BigInt{
public:
    BigInt();
    explicit BigInt(int);
    explicit BigInt(std::string);
    BigInt(const BigInt&);
    BigInt(BigInt&&);
    
    BigInt& operator=(const BigInt&);
    BigInt& operator=(BigInt&&);

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
    
    BigInt operator~() const;
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
    explicit operator std::string() const;

    size_t size() const;

    friend std::ostream& operator<<(std::ostream&, const BigInt&);

    bool operator>(const int&) const;
    BigInt& operator+=(const int&);
    BigInt& operator/=(const int&);
    int* getVectorPointer();
private:
    std::vector<int> data;
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

std::ostream& operator<<(std::ostream&, const BigInt&);

BigInt operator*(const BigInt& left, const int& right);
BigInt operator%(const BigInt& left, const int&);
#endif //LAB1_BIGINT_H
