#include <iostream>
#include <cassert>
#include "format.h"
using namespace std;
int main() {
    string form = "{20}+{1} = {0}";
    string x;

    x = format("{1}+{1} = {0}", 2, "one");
    assert(x == "one+one = 2");
    x = format("Hello, {0} with floating number {2} and integer number {1}", "Arithmetic World", 5, 3.1446);
    assert(x == "Hello, Arithmetic World with floating number 3.1446 and integer number 5");
    try {
        x = format("{20}+{1} = {0}", 2, "one");
    }
    catch (runtime_error) {
        cout << "exception successful\n";
        x = "";
    }
    cout << "All tests passed\n";
    return 0;
}