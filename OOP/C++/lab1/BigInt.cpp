#include <iostream>
#include <string>
#include "BigInt.h"

BigInt:: BigInt(){
    sign = false;
    data.push_back(0);
}

std::vector<int> createVector(long long int newValue){
    std::vector<int> data;
    do{
        data.push_back(newValue % BASE);
        newValue /= BASE;
    }
    while (newValue > 0);
    return data;
}

long long int abs(long long int input){
    return (input < 0) ? input * (-1) : input;
}

BigInt::BigInt(int input){
    auto newValue = static_cast<long long int>(input);
    sign = (newValue < 0);
    data = createVector(abs(newValue));
}

bool isSymbCorrect (char symb){
    if ((('0' <= symb) && (symb <= '9')) || (symb == '-')) return true;
    else return false;
}

std::vector<int> createVector(std::string strBigInt){
    std::vector<int> data;
    int newItem = 0, digits = 1, pow = 1;
    for (int i = strBigInt.length() - 1; i >= 0; --i){
        if (!isSymbCorrect(strBigInt[i])) throw std::invalid_argument("invalid symbol");
        if (strBigInt[i] != '-')
            newItem = pow * (strBigInt[i] - '0') + newItem;
        if ((digits == 9) || (i == 0)) {
            data.push_back(newItem);
            newItem = 0;
            digits = 1;
            pow = 1;
        }
        else{
            pow *= 10;
            ++digits;
        }
    }

    return data;
}

void deleteInvalidZeros(std::vector<int> &data) {
    if (data.size()==1) return;
    for (int i = data.size()-1; i >= 1; --i){
        if (data[i] != 0) break;
        if (data[i] == 0) data.pop_back();
    }
}

BigInt::BigInt(std::string input) {
    sign = (input[0] == '-');
    data = createVector(input);
    deleteInvalidZeros(data);
    if ((data[0] == 0) && (data.size() == 1)) sign = false;
}

BigInt::BigInt(const BigInt& other){
    this->sign = other.sign;
    this->data = other.data;
}

BigInt::BigInt(BigInt&& other){
    std::swap(this->data, other.data);
    std::swap(this->sign, other.sign);
}

BigInt& BigInt::operator=(BigInt&& right){
    std::swap(this->data, right.data);
    std::swap(this->sign, right.sign);

    return *this;
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
    *this = *this -  dec;
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
        ++negation;
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
//space ship ooperator
bool BigInt::operator<(const BigInt& second) const {
    if (*this == second) return false;
    if (this->sign && !second.sign) return true;
    if (!this->sign && second.sign) return false;
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
    copy.sign = !(copy.isZero(copy)) && !copy.sign;

    return copy;
}

BigInt absBigInt(const BigInt& num){
    return num > 0 ? num : (-num);
}

BigInt& BigInt::operator+=(const BigInt &right ){
    if (this->sign == right.sign){
        int shiftOne = 1;
        for (int i = 0; i < right.data.size(); ++i){
            if (i == this->data.size()) this->data.push_back(0);
            this->data[i] += right.data[i];
            if (this->data[i] >= BASE){
                this->data[i] %= BASE;
                if (i == this->data.size() - 1) this->data.push_back(shiftOne);
                else this->data[i+1] += shiftOne;
            }
        }
        if ((this->size()==sizeof(int)) && (int)(*this) == 0) this->sign = false;
        return *this;
    }
    this->sign = !this->sign;
    *this -= right;
    this->sign = !this->sign;
    if ((this->size()==sizeof(int)) && (int)(*this) == 0) this->sign = false;
    return *this;
}

BigInt& BigInt::operator+=(const int &rightInt){
    BigInt right(rightInt);
    *this = *this + right;
    return *this;
}

BigInt& BigInt::operator-=(const BigInt &right){
    if (this->sign != right.sign){
        this->sign = !this->sign;
        *this += right;
        this->sign = !this->sign;
        return *this;
    }
    bool resultSign = (*this < right);
    if (this->data.size() < right.data.size()) this->data.resize(right.data.size(), 0);
    int take = 0;
    for (int i = 0; i < right.data.size() || take != 0; ++i){
        this->data[i] -= take + (i < right.data.size() ? right.data[i] : 0);
        if (this->data[i] < 0) {
            this->data[i] = (resultSign || right.sign) ? this->data[i] * (-1) : this->data[i] + BASE;
            take = (resultSign || right.sign) ? 0 : 1;
        }
        else take = 0;
    }
    this->sign = resultSign;
    deleteInvalidZeros(this->data);
    return *this;
}

BigInt& BigInt::operator*=(const BigInt &right){
    BigInt result;
    result.data.resize(this->data.size() + right.data.size());
    for (int i = 0; i < right.data.size(); ++i){
        int carry = 0;
        for (int j = 0; j < this->data.size() || carry != 0; ++j){
            long long int cur = result.data[i + j] + 1LL * right.data[i] * (j < this->data.size() ? this->data[j] : 0) + carry;
            result.data[i+j] = static_cast<int>(cur % BASE);
            carry = static_cast<int>(cur / BASE);

        }
    }
    deleteInvalidZeros(result.data);
    result.sign = (this->sign != right.sign);
    *this = result;
    return *this;
}

void shiftRight(std::vector<int> &shift){
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

BigInt convertIntToBigInt(int item){
    BigInt conv(item);
    return conv;
}

int findElemOfResult(const BigInt& cur, const BigInt& divider){
    int elemOfResult = 0, left = 0, right = BASE;
    while (left <= right){
        int middle = (left + right)/2;
        BigInt tmp = convertIntToBigInt(middle) * divider;
        if (tmp <= cur){
            elemOfResult = middle;
            left = middle + 1;
        }
        else right = middle - 1;
    }
    return elemOfResult;
}

bool BigInt::isZero(const BigInt& v){
    if ((v.data.size() == 1) && (v.data[0] == 0)) return true;
    else return false;
}

BigInt& BigInt::operator/=(const BigInt &right){
    if (isZero(right)) throw std::invalid_argument("you tried divide by zero");
    BigInt shift, result;
    BigInt divider = right;
    divider.sign = false;
    result.data.resize(this->data.size());
    for (int i = this->data.size() - 1; i >= 0; --i){
        shiftRight(shift.data);
        shift.data[0] = this->data[i];
        deleteInvalidZeros(shift.data);
        int elemOfResult = findElemOfResult(shift, divider);
        result.data[i] = elemOfResult;
        shift = shift - (convertIntToBigInt(elemOfResult) * divider);
    }
    deleteInvalidZeros(result.data);
    result.sign = (this->sign != right.sign);
    *this = result;
    return *this;
}

BigInt& BigInt::operator%=(const BigInt& right){
    this->sign = false;
    *this = *this - ((*this / right) * right);
    return *this;
}

BigInt operator+(const BigInt& left, const BigInt& right) {
    BigInt result = left;
    result += right;
    return result;
}

BigInt operator-(const BigInt& left, const BigInt& right) {
    BigInt result = left;
    result -= right;
    return result;
}

BigInt operator*(const BigInt& left, const BigInt& right){
    BigInt result = left;
    result *= right;
    return result;
}

BigInt operator/(const BigInt& left, const BigInt& right){
    BigInt result = left;
    result /= right;
    return result;
}

BigInt operator%(const BigInt& left, const BigInt& right){
    BigInt result = left;
    result %= right;
    return result;
}

int calcCountOfZeros(int n){
    if (n == 0) return 8;
    int length = 0;
    while(n > 0){
        ++length;
        n /= 10;
    }
    return 9 - length;
}

BigInt::operator int() const {
    int conv = 0, pow = 1;
    for (int i = 0; i < this->data.size(); ++i){
        conv += this->data[i]*pow;
        pow *= BASE;
    }
    if (this->sign) conv *= (-1);
    return conv;
}

std::string convertIntToStr(int item){
    if (item == 0) return "0";
    std::string strInt;
    while (item > 0){
        strInt = (char)((item % 10) + '0') + strInt;
        item /= 10;
    }
    return strInt;
}

void printZeros(std::string* strBigInt, int countOfZeros){
    for (int i = 1; i <= countOfZeros; ++i)
        *strBigInt = *strBigInt + '0';
}

std::string convertBigIntToStr(const std::vector<int> &data){
    std::string strBigInt;
    for (int i = data.size() - 1; i >= 0; --i){
        int countOfZeros = calcCountOfZeros(data[i]);
        if (i != data.size() - 1) printZeros(&strBigInt, countOfZeros);
        strBigInt += convertIntToStr(data[i]);
    }

    return strBigInt;
}

BigInt::operator std::string() const{
    std::string strBigInt = convertBigIntToStr(this->data);
    if (this->sign) strBigInt = '-' + strBigInt;
    return strBigInt;
}

size_t BigInt::size() const{
    return this->data.size() * sizeof(int);
}

std::ostream& operator<<(std::ostream& stream, const BigInt& num){
    return stream << (std::string)num;
}

std::string convertBigIntToBin(BigInt num){
    num = absBigInt(num);
    std::string bin;
    while (num > 0){
        bin = convertIntToStr((int) (num % 2)) + bin;
        num /= 2;
    }
    return bin;
}

void addNullBits(std::string& bin, int count){
    while (count > 0){
        bin = "0" + bin;
        --count;
    }
}

void alignBits(std::string& leftBin, std::string& rightBin){
    int difference = leftBin.size() - rightBin.size();
    if (difference > 0) addNullBits(rightBin, difference);
    else if (difference < 0) addNullBits(leftBin, abs(difference));
}

void deleteLeadBits(std::string& bin){
    while ((bin[0] == '0') && (bin.size() > 1))
        bin.erase(0, 1);
}

std::string applyBinOperatorAND(const std::string& left, const std::string& right){
    std::string resultBin;
    for (int i = 0; i < left.size(); ++i){
        if ((left[i] == '0') || (right[i] == '0')) resultBin += '0';
        else resultBin += '1';
    }
    deleteLeadBits(resultBin);
    return resultBin;
}

std::string applyBinOperatorOR(const std::string& left, const std::string& right){
    std::string resultBin;
    for (int i = 0; i < left.size(); ++i){
        if ((left[i] == '1') || (right[i] == '1')) resultBin += '1';
        else resultBin += '0';
    }
    deleteLeadBits(resultBin);
    return resultBin;
}

std::string applyBinOperatorXOR(const std::string& left, const std::string& right){
    std::string resultBin;
    for (int i = 0; i < left.size(); ++i){
        if (left[i] != right[i]) resultBin += '1';
        else resultBin += '0';
    }
    deleteLeadBits(resultBin);
    return resultBin;
}

BigInt convertBinaryToBigInt(const std::string& bin){
    BigInt result(0);
    BigInt pow(1);
    for (int i = 0; i < bin.size(); ++i){
        result += pow * (bin[bin.size() - 1 - i] - '0');
        pow = pow * 2;
    }
    return result;
}

BigInt operator&(const BigInt& left, const BigInt& right){
    BigInt result = left;
    result &= right;
    return result;
}

BigInt operator|(const BigInt& left, const BigInt& right){
    BigInt result = left;
    result |= right;
    return result;
}

BigInt operator^(const BigInt& left, const BigInt& right){
    BigInt result = left;
    result ^= right;
    return result;
}

BigInt& BigInt::operator&=(const BigInt& right){
    std::string leftBin = convertBigIntToBin(*this);
    std::string rightBin = convertBigIntToBin(right);
    alignBits(leftBin, rightBin);
    std::string resultBin = applyBinOperatorAND(leftBin, rightBin);
    BigInt result = convertBinaryToBigInt(resultBin);
    result.sign = (this->sign && right.sign);
    *this = result;
    return *this;
}

BigInt& BigInt::operator|=(const BigInt& right){
    std::string leftBin = convertBigIntToBin(*this);
    std::string rightBin = convertBigIntToBin(right);
    alignBits(leftBin, rightBin);
    std::string resultBin = applyBinOperatorOR(leftBin, rightBin);
    BigInt result = convertBinaryToBigInt(resultBin);
    result.sign = (this->sign || right.sign);
    *this = result;
    return *this;
}

BigInt& BigInt::operator^=(const BigInt& right){
    std::string leftBin = convertBigIntToBin(*this);
    std::string rightBin = convertBigIntToBin(right);
    alignBits(leftBin, rightBin);
    std::string resultBin = applyBinOperatorXOR(leftBin, rightBin);
    BigInt result = convertBinaryToBigInt(resultBin);
    result.sign = (this->sign != right.sign);
    *this = result;
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

int* BigInt::getVectorPointer() {
    return &(this->data[0]);
}
