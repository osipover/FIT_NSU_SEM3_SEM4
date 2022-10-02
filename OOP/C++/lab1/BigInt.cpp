#include <iostream>
#include <string>
#include <cmath>
#include "BigInt.h"
using namespace std;

BigInt:: BigInt(){
    sign = false;
    data.push_back(0);
}

BigInt::BigInt(int input){
    sign = (input < 0);
    input = abs(input);
    data.push_back(input);
}

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
        if (this->data[i] != second.data.at(i))
            return false;
    }
    return true;
}

bool BigInt::operator!=(const BigInt& second) const {
    return !(*this == second);
}

bool BigInt::operator<(const BigInt& second) const {
    if (*this == second) return false;
    if (this->sign && !second.sign) return true;
    if (!(this->sign) && second.sign) return false;
    if (!sign){
        if (this->data.size() < second.data.size()) return true;
        if (this->data.size() > second.data.size()) return false;
        for (int i = data.size()-1; i >= 0; --i){
            if (this->data[i] < second.data[i]) return true;
            if (this->data[i] > second.data[i]) return false;
        }
        return false;
    }
    else {
        if (this->data.size() > second.data.size()) return true;
        if (this->data.size() < second.data.size()) return false;
        for (int i = data.size()-1; i >= 0; --i){
            if (this->data[i] > second.data[i]) return true;
            if (this->data[i] < second.data[i]) return false;
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
            left.data[i] += right.data[i];
            if (left.data[i] >= left.base){
                left.data[i] %= 1000000000;
                if (i == left.data.size() - 1) left.data.push_back(shiftOne);
                else left.data[i+1] += shiftOne;
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
        left.data[i] -= take + (i != right.data.size() ? right.data[i] : 0);
        if (left.data[i] < 0) {
            left.data[i] += left.base;
            take = 1;
        }
        else take = 0;
    }
    return left;
}

BigInt operator*(const BigInt& left, const BigInt& right){
    BigInt result;
    result.data.resize(left.data.size() + right.data.size());
    for (int i = 0; i < right.data.size(); ++i){
        int carry = 0;
        for (int j = 0; j < left.data.size() || carry != 0; ++j){
            long long int cur = result.data[i + j] + 1LL * right.data[i] * (j < left.data.size() ? left. data[j] : 0) + carry;
            result.data[i+j] += static_cast<int>(cur % result.base);
            carry = static_cast<int>(cur / result.base);

        }
    }
    DeleteInvalidZeros(result.data);
    result.sign = (left.sign != right.sign);
    return result;
}

void ShiftRight(vector<int> &shift){
    if (shift.empty()){
        shift.push_back(0);
        return;
    }
    shift.push_back(shift[shift.size()-1]);
    for (auto i = shift.size() - 2; i > 0; --i){
        shift[i] = shift[i - 1];
    }
    shift[0] = 0;
}
/*
int FindDigitQuot(const BigInt& divider){
    int digitQuot = 0, left = 0, right = 1000000000;
    while (left <= right){
        BigInt middle((left + right)/2);


    }
    return digitQuot;
}

BigInt operator/(const BigInt& left, const BigInt& right){
    BigInt shift, result;
    result.data.resize(left.data.size());
    for (auto i = left.data.size() - 1; i >= 0; --i){
        ShiftRight(shift.data);
        shift.data[0] = left.data[i];
        //int digitQuot = FindDigitOfQuot();
    }
}*/

int CalcCountOfZeros(int n){
    int length = 0;
    while(n > 0){
        ++length;
        n /= 10;
    }
    return 9 - length;
}

void PrintZeros(ostream& stream, int countOfZeros){
    for (int i = 1; i <= countOfZeros; ++i)
        stream << 0;
}

BigInt::operator int() const {
    return this->data[0];
}

string ConvertIntToStr(int item){
    string strInt = "";
    while (item > 0){
        strInt = (char)((item % 10) + '0') + strInt;
        item /= 10;
    }
    return strInt;
}

string ConvertBigIntToStr(const vector<int> &data){
    string strBigInt = "";
    for (int i = data.size() - 1; i >= 0; --i){
        strBigInt += ConvertIntToStr(data[i]);
    }
    return strBigInt;
}

BigInt::operator string() const{
    string strBigInt = ConvertBigIntToStr(this->data);
    return strBigInt;
}

size_t BigInt::size() const{
    return this->data.size()*sizeof(int);
}

ostream& operator<<(ostream& stream, const BigInt& item){
    if (item.sign)
        stream << '-';
    for (int i = item.data.size()-1; i >= 0; --i){
        int countOfZeros = CalcCountOfZeros(item.data[i]);
        if (i != item.data.size()-1)
            PrintZeros(stream, countOfZeros);
        stream << item.data[i];
    }
    return stream;
}
