#include <iostream>
#include <string>
#include <cmath>
#include "BigInt.h"
using namespace std;

vector<int> CreateVector(string BigIntInStr){
    vector<int> BigInt;
    int newItem = 0, digits = 1, pow = 1;
    for (int i = BigIntInStr.length() - 1; i >= 0; --i){
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
    for (int i = num.size()-1; i >= 0; --i){
        int countOfZeros = CalcCountOfZeros(num.at(i));
        if (i != num.size()-1)
            PrintZeros(countOfZeros);
        cout << num.at(i);
    }
    cout << endl;
}

BigInt:: BigInt(){

}

BigInt:: ~BigInt(){

}

BigInt::BigInt(int input){
    sign = (input > 0);
    input = abs(input);
    num.push_back(input);
}

BigInt::BigInt(string input) {
    sign = (input[0] == '-');
    num = CreateVector(input);
}

BigInt& BigInt::operator=(const BigInt &second) {
    num = second.num;
    sign = second.sign;
    return *this;
}

bool IsOverflow(int BigIntItem){
    return (BigIntItem == 1000000000);
}

BigInt BigInt::operator~() const{
    BigInt add;
    for (int i = 0; i < num.size(); ++i)
        add.num.push_back(~num.at(i));

    if (!add.sign){
        add.sign = true;
        //to finish with "-"
    }
    return add;
}

BigInt& BigInt::operator++() {
    for (int i = 0; i < num.size(); ++i){
        num.at(i)++;
        if (IsOverflow(num.at(i))){
            num.at(i) = 0;
            if (i == num.size()-1){
                num.push_back(1);
                break;
            }
        }
        else
            break;
    }
    return *this;
}
