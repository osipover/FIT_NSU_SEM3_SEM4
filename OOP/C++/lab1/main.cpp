#include <iostream>
#include "BigInt.h"
using namespace std;

int main() {
    BigInt a("-123");
    BigInt b = a--;
    b.Print();
    a.Print();

    return 0;
}


