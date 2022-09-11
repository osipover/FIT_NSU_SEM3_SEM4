#include <iostream>
#include <string>
#include "BigInt.h"
using namespace std;

int main() {
    string BigIntInStr = "123456789123";
    BigInt a(-3);
    a = ~a;
    a.Print();
    int b = -100;
    b = ~(-100);
    cout << b;
}

