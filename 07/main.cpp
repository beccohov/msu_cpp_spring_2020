#include <iostream>
#include <vector>
#include <assert.h>
#include "Vector.h"
//#include "iterators.h"
using namespace std;
int main() {
    Vector<int> implementation(5);
    vector<int> stl(5);
    assert(implementation.empty() == false);
    assert(implementation[0] == stl[0]);
    implementation.reserve(5);
    stl.reserve(5);
    assert(implementation.size() != 10);
    implementation.push_back(5);
    stl.push_back(5);
    assert(implementation.back() == stl.back());
    implementation.pop_back();
    stl.pop_back();
    assert(implementation.size() == stl.size());
    assert(implementation.back() == stl.back());
    implementation.resize(7);
    stl.resize(7);
    implementation.push_back(7);
    stl.push_back(7);
    implementation.push_back(10);
    stl.push_back(10);
    assert(implementation.size() == stl.size());
    assert(implementation.back() == stl.back());
    iterator_<int> el = implementation.begin();
    auto second = stl.begin();
    for (; el != implementation.end(); ++el,++second)
    {
        int stl_element = *second;
        int implementation_element = *el;
        assert(stl_element == implementation_element);
    }
    riterator<int> rel = implementation.rbegin();
    auto rsecond = stl.rbegin();
    for (; rel != implementation.rend(); ++rel, ++rsecond)
    {
        int stl_element = *rsecond;
        int implementation_element = *rel;
        assert(stl_element == implementation_element);
    }
    cout << "All tests passed successfully\n";
    return 0;
}