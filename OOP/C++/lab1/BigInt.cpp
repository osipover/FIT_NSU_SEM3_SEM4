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
            newItem = pow*(BigIntInStr[i] - '0') + newItem;
        if ((digits == 9) || (i == 0)){
            BigInt.push_back(newItem);
            newItem = 0;
            digits = 0;
            pow = 1;
        }
        else{
            pow*=10;
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
    if (sign == true)
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

BigInt::BigInt(string input) {
    sign = (input[0] == '-');
    data = CreateVector(input);
}

BigInt& BigInt::operator=(const BigInt &second) {
    data = second.data;
    sign = second.sign;
    return *this;
}

bool IsOverflow(int BigIntItem){
    return (BigIntItem == 1000000000);
}

BigInt& BigInt::operator++() {
    if (!sign){
        for (int i = 0; i < data.size(); ++i){
            data.at(i)++;
            if (IsOverflow(data.at(i))){
                data.at(i) = 0;
                if (i == data.size()-1){
                    data.push_back(1);
                    break;
                }
            }
            else
                break;
        }
    }
    else {
        for (int i = 0; i < data.size(); ++i){
            if (data.at(i) == 0){
                data.at(i) = 999999999;
            }
            else{
                data.at(i)--;
                break;
            }
        }
        if ((data.at(data.size()-1) == 0) && (data.size() > 1))
            data.pop_back();
        if ((data.at(0) == 0) && (data.size() == 1))
            sign = false;
    }
    return *this;
}

BigInt& BigInt::operator--(){
    if (!sign){
        for (int i = 0; i < data.size(); ++i){
            if ((data.at(i) == 0) && (data.size() == 1)){
                data.at(i) = 1;
                sign = true;
            }
            else if ((data.at(i) == 0) && (data.size() > 1)){
                data.at(i) = 999999999;
            }
            else{
                data.at(i)--;
                break;
            }
        }
        if ((data.at(data.size()-1) == 0) && (data.size() > 1))
            data.pop_back();
    }
    else {
        for (int i = 0; i < data.size(); ++i){
            data.at(i)++;
            if (IsOverflow(data.at(i))){
                data.at(i) = 0;
                if (i == data.size()-1){
                    data.push_back(1);
                    break;
                }
            }
            else
                break;
        }
    }
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

bool BigInt::operator==(const BigInt& second) const {
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

