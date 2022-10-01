#include <iostream>
#include <string>
#include <cmath>
#include "BigInt.h"
using namespace std;

vector<int> CreateVector(string BigIntInStr){
    vector<int> BigInt;
    int newItem = 0, digits = 1, pow = 1;
    for (int i = BigIntInStr.length() - 1; i >= 0; --i){
        if (BigIntInStr[i] != '-')
            newItem = pow * (BigIntInStr[i] - '0') + newItem;
        if ((digits == 9) || ((i == 0) && (BigIntInStr[i] != '-'))) {
            BigInt.push_back(newItem);
            newItem = 0;
            digits = 1;
            pow = 1;
        }
        else{
            pow *= 10;
            ++digits;
        }
    }
    return BigInt;
}

int CalcCountOfZeros(int n){
    int length = 0;
    while(n > 0){
        ++length;
        n /= 10;
    }
    return 9 - length;
}

void PrintZeros(int countOfZeros){
    for (int i = 1; i <= countOfZeros; ++i)
        cout << 0;
}

void BigInt::Print(){
    if (sign)
        cout << '-';
    for (int i = data.size()-1; i >= 0; --i){
        int countOfZeros = CalcCountOfZeros(data.at(i));
        if (i != data.size()-1)
            PrintZeros(countOfZeros);
        cout << data.at(i);
    }
    cout << endl;
}

BigInt:: BigInt(){
    sign = false;
    data.push_back(0);
}

BigInt::BigInt(int input){
    sign = (input < 0);
    input = abs(input);
    data.push_back(input);
}

void DeleteInvalidZeros(vector<int> &data) {
    if (data.size()==1) return;
    for (int i = data.size()-1; i >= 1; --i){
        if (data[i] == 0) data.pop_back();
    }
}

BigInt::BigInt(string input) {
    sign = (input[0] == '-');
    data = CreateVector(input);
    DeleteInvalidZeros(data);
}

BigInt& BigInt::operator=(const BigInt &second) {
    data = second.data;
    sign = second.sign;
    return *this;
}

bool IsOverflow(int BigIntItem){
    return (BigIntItem >= 1000000000);
}

BigInt& BigInt::operator++() {
    BigInt inc(1);
    *this += inc;
    return *this;
}

BigInt& BigInt::operator--(){
    BigInt dec(1);
    *this -= dec;
    return *this;
}

BigInt BigInt::operator++(int){
    BigInt copy = *this;
    ++(*this);
    return copy;
}

BigInt BigInt::operator--(int){
    BigInt copy = *this;
    --(*this);
    return copy;
}

BigInt BigInt::operator~() const {
    BigInt negation = *this;
    if (!sign) {
        ++negation;
        negation.sign = true;
    }
    else{
        --negation;
        negation.sign = false;
    }
    return negation;
}



bool BigInt::operator==(const BigInt &second) const {
    if (this->sign != second.sign)
        return false;
    if (data.size() != second.data.size())
        return false;
    for (int i = data.size()-1; i >= 0; --i){
        if (this->data.at(i) != second.data.at(i))
            return false;
    }
    return true;
}

bool BigInt::operator!=(const BigInt& second) const {
    return !(*this == second);
}

bool BigInt::operator<(const BigInt& second) const {
    if (*this == second)
        return false;

    if (this->sign && !second.sign)
        return true;
    if (!(this->sign) && second.sign)
        return false;

    if (!sign){
        if (this->data.size() < second.data.size())
            return true;
        if (this->data.size() > second.data.size())
            return false;
        for (int i = data.size()-1; i >= 0; --i){
            if (this->data.at(i) < second.data.at(i))
                return true;
            if (this->data.at(i) > second.data.at(i))
                return false;
        }
        return false;
    }
    else {
        if (this->data.size() > second.data.size())
            return true;
        if (this->data.size() < second.data.size())
            return false;
        for (int i = data.size()-1; i >= 0; --i){
            if (this->data.at(i) > second.data.at(i))
                return true;
            if (this->data.at(i) < second.data.at(i))
                return false;
        }
        return false;
    }
}

bool BigInt::operator>(const BigInt& second) const {
    return !(*this < second) && (*this != second);
}

bool BigInt::operator<=(const BigInt& second) const {
    return (*this < second) || (*this == second);
}

bool BigInt::operator>=(const BigInt& second) const {
    return (*this > second) || (*this == second);
}

BigInt BigInt::operator+() const {
    BigInt copy = *this;
    return copy;
}

BigInt BigInt::operator-() const {
    BigInt copy = *this;
    copy.sign = !copy.sign;
    return copy;
}

BigInt& BigInt::operator+=(const BigInt &right ){
    *this = *this + right;
    return *this;
}

BigInt& BigInt::operator-=(const BigInt &right){
    *this = *this - right;
    return *this;
}

BigInt operator+(BigInt left, const BigInt& right) {
    if (left.sign == right.sign){
        int shiftOne = 1;
        for (int i = 0; i < right.data.size(); ++i){
            left.data.at(i) += right.data.at(i);
            if (left.data.at(i) >= left.base){
                left.data.at(i) %= 1000000000;
                if (i == left.data.size() - 1) left.data.push_back(shiftOne);
                else left.data.at(i+1) += shiftOne;
            }
        }
        return left;
    }
    else if (left.sign) return right - (-left);
    else return left - (-right);
}

BigInt operator-(BigInt left, const BigInt& right) {
    if (right.sign) return left + (-right);
    else if (left.sign) return -(-left + right);
    else if (left < right) return -(right - left);
    int take = 0;
    for (int i = 0; i < right.data.size() || take != 0; ++i){
        left.data.at(i) -= take + (i != right.data.size() ? right.data.at(i) : 0);
        if (left.data.at(i) < 0) {
            left.data.at(i) += left.base;
            take = 1;
        }
        else take = 0;
    }
    return left;
}
