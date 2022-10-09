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
        if ((digits == 9) || (i == 0)) {
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

BigInt absBigInt(const BigInt& num){
    return num > 0 ? num : (-num);
}

BigInt& BigInt::operator+=(const BigInt &right ){
    *this = *this + right;
    return *this;
}

BigInt& BigInt::operator+=(const int &rightInt){
    BigInt right(rightInt);
    *this = *this + right;
    return *this;
}

BigInt& BigInt::operator-=(const BigInt &right){
    *this = *this - right;
    return *this;
}

BigInt& BigInt::operator*=(const BigInt &right){
    *this = *this * right;
    return *this;
}


BigInt& BigInt::operator/=(const BigInt &right){
    *this = *this / right;
    return *this;
}

BigInt& BigInt::operator%=(const BigInt& right){
    *this = *this % right;
    return *this;
}

BigInt operator+(BigInt left, const BigInt& right) {
    if (left.sign == right.sign){
        int shiftOne = 1;
        for (int i = 0; i < right.data.size(); ++i){
            if (i == left.data.size()) left.data.push_back(0);
            left.data[i] += right.data[i];
            if (left.data[i] >= left.base){
                left.data[i] %= 1000000000;
                if (i == left.data.size() - 1) left.data.push_back(shiftOne);
                else left.data[i+1] += shiftOne;
            }
        }
        if ((size(left)==sizeof(int)) && (int)left == 0) left.sign = false;
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
    DeleteInvalidZeros(left.data);
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

BigInt ConvertIntToBigInt(int item){
    BigInt converted(item);
    return converted;
}

int FindElemOfResult(const BigInt& cur, const BigInt& divider){
    int elemOfResult = 0, left = 0, right = 1000000000;
    while (left <= right){
        int middle = (left + right)/2;
        BigInt tmp = ConvertIntToBigInt(middle) * divider;
        if (tmp <= cur){
            elemOfResult = middle;
            left = middle + 1;
        }
        else right = middle - 1;
    }
    return elemOfResult;
}

BigInt operator/(const BigInt& left, const BigInt& right){
    BigInt shift, result;
    BigInt divider = right;
    divider.sign = false;
    result.data.resize(left.data.size());
    for (int i = left.data.size() - 1; i >= 0; --i){
        ShiftRight(shift.data);
        shift.data[0] = left.data[i];
        DeleteInvalidZeros(shift.data);
        int elemOfResult = FindElemOfResult(shift, divider);
        result.data[i] = elemOfResult;
        shift = shift - (ConvertIntToBigInt(elemOfResult) * divider);
    }
    DeleteInvalidZeros(result.data);
    result.sign = (left.sign != right.sign);
    return result;
}

BigInt operator%(const BigInt& left, const BigInt& right){
    BigInt result = left;
    result.sign = false;
    result = result - ((result / right) * right);
    return result;
}

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

//переделать
BigInt::operator int() const {
    return this->data[0];
}

string ConvertIntToStr(int item){
    if (item == 0) return "0";
    string strInt;
    while (item > 0){
        strInt = (char)((item % 10) + '0') + strInt;
        item /= 10;
    }
    return strInt;
}

string ConvertBigIntToStr(const vector<int> &data){
    string strBigInt;
    for (int i = data.size() - 1; i >= 0; --i)
        strBigInt += ConvertIntToStr(data[i]);
    return strBigInt;
}

BigInt::operator string() const{
    string strBigInt = ConvertBigIntToStr(this->data);
    return strBigInt;
}

size_t BigInt::size() const{
    return this->data.size() * sizeof(int);
}

ostream& operator<<(ostream& stream, const BigInt& num){
    if (num.sign)
        stream << '-';
    for (int i = num.data.size() - 1; i >= 0; --i){
        int countOfZeros = CalcCountOfZeros(num.data[i]);
        if (i != num.data.size() - 1)
            PrintZeros(stream, countOfZeros);
        stream << num.data[i];
    }
    return stream;
}

string ConvertBigIntToBin(BigInt num){
    num = absBigInt(num);
    string bin;
    while (num > 0){
        bin = ConvertIntToStr((int)(num % 2)) + bin;
        num /= 2;
    }
    return bin;
}

void AddNullBits(string& bin, int count){
    while (count > 0){
        bin = "0" + bin;
        --count;
    }
}

void AlignBits(string& leftBin, string& rightBin){
    int difference = leftBin.size() - rightBin.size();
    if (difference > 0) AddNullBits(rightBin, difference);
    else if (difference < 0) AddNullBits(leftBin, abs(difference));
}

void DeleteLeadBits(string& bin){
    while ((bin[0] == '0') && (bin.size() > 1))
        bin.erase(0, 1);
}

string BinOperatorAND(const string& left, const string& right){
    string resultBin;
    for (int i = 0; i < left.size(); ++i){
        if ((left[i] == '0') || (right[i] == '0')) resultBin += '0';
        else resultBin += '1';
    }
    DeleteLeadBits(resultBin);
    return resultBin;
}

string BinOperatorOR(const string& left, const string& right){
    string resultBin;
    for (int i = 0; i < left.size(); ++i){
        if ((left[i] == '1') || (right[i] == '1')) resultBin += '1';
        else resultBin += '0';
    }
    DeleteLeadBits(resultBin);
    return resultBin;
}

string BinOperatorXOR(const string& left, const string& right){
    string resultBin;
    for (int i = 0; i < left.size(); ++i){
        if (left[i] != right[i]) resultBin += '1';
        else resultBin += '0';
    }
    cout << resultBin << endl;
    DeleteLeadBits(resultBin);
    return resultBin;
}

BigInt ConvertBinaryToBigInt(const string& bin){
    BigInt result(0);
    BigInt pow(1);
    for (int i = 0; i < bin.size(); ++i){
        result += pow * (bin[bin.size() - 1 - i] - '0');
        pow = pow * 2;
    }
    return result;
}

BigInt operator&(const BigInt& left, const BigInt& right){
    string leftBin = ConvertBigIntToBin(left);
    string rightBin = ConvertBigIntToBin(right);
    AlignBits(leftBin, rightBin);
    string resultBin = BinOperatorAND(leftBin, rightBin);
    BigInt result = ConvertBinaryToBigInt(resultBin);
    result.sign = (left.sign && right.sign);
    return result;
}

BigInt operator|(const BigInt& left, const BigInt& right){
    string leftBin = ConvertBigIntToBin(left);
    string rightBin = ConvertBigIntToBin(right);
    AlignBits(leftBin, rightBin);
    string resultBin = BinOperatorOR(leftBin, rightBin);
    BigInt result = ConvertBinaryToBigInt(resultBin);
    result.sign = (left.sign || right.sign);
    return result;
}

BigInt operator^(const BigInt& left, const BigInt& right){
    string leftBin = ConvertBigIntToBin(left);
    string rightBin = ConvertBigIntToBin(right);
    AlignBits(leftBin, rightBin);
    string resultBin = BinOperatorXOR(leftBin, rightBin);
    BigInt result = ConvertBinaryToBigInt(resultBin);
    result.sign = (left.sign != right.sign);
    return result;
}

BigInt& BigInt::operator&=(const BigInt& right){
    *this = *this & right;
    return *this;
}

BigInt& BigInt::operator|=(const BigInt& right){
    *this = *this | right;
    return *this;
}

BigInt& BigInt::operator^=(const BigInt& right){
    *this = *this ^ right;
    return *this;
}

bool BigInt::operator>(const int& rightInt) const {
    BigInt right(rightInt);
    return *this > right;
}

BigInt operator*(const BigInt& left, const int& rightInt){
    BigInt right(rightInt);
    return left * right;
}

BigInt operator%(const BigInt& left, const int& rightInt){
    BigInt right(rightInt);
    return left % right;
}

BigInt& BigInt::operator/=(const int& rightInt){
    BigInt right(rightInt);
    *this = *this / right;
    return *this;
}
