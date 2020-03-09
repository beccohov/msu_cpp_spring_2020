#include <iostream>
#include <cassert>
#include "allocator.h"
using namespace std;
void Test() {
    LinearAllocator allocator;
    allocator.initAllocator(0);
    assert(allocator.alloc(0) == nullptr); //Zero case
    allocator.initAllocator(5000);
    assert(allocator.alloc(5000) != nullptr); // Full request case
    allocator.reset();
    assert(allocator.alloc(5001) == nullptr); //Out of range case
    allocator.reset();
    assert(allocator.alloc(1000) != nullptr); // Common case, testing reset
    allocator.reset();
    allocator.alloc(4000);
    assert(allocator.alloc(1001) == nullptr);// Overflow
    assert(allocator.alloc(1000) != nullptr); // Border case
    allocator.reset();
    cout << "All tests passed\n";
}
int main() {
    Test();
    return 0;
}