#include <iostream>
#include "BigInt.h"

using namespace std;

int main() {
    BigInt a("111111111123145"), b("1111111111121");
    BigInt c = a & b;
    cout << c;
    return 0;
}
