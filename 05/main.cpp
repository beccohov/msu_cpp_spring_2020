#include <iostream>
#include <cassert>
#include <stdint.h>
#include "BigInt.h"
using namespace std;
int main() {
    unsigned long long a = 1000000000;
    BigInt i,j,k;
    j = 1999999999;
    i = a;
    k = j - i;
    assert(k == 999999999);
    assert(k > 10000);
    assert(k + 1 == 1000000000);
    cout << "All tests passed\n";
    return 0;
}
