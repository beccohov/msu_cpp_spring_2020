#include <iostream>
#include <sstream>
#include <cassert>
#include "serializer.h"
#include "deserializer.h"
using namespace std;
struct Data {
    uint64_t a;
    bool b;
    uint64_t c;
    template<typename Serializer>
    Errors serialize(Serializer& serializer) {
        return serializer(a, b, c);
    }
    template <typename Deserializer>
    Errors deserialize(Deserializer& deserializer) {
        return deserializer(a, b, c);
    }
};
int main() {
    Data x{ 1, true, 2 };
    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    Data y{ 0, false, 0 };

    Deserializer deserializer(stream);
    const Errors err = deserializer.load(y);

    assert(err == Errors::NoError);

    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);
    cout << "All tests passed\n";
    return 0;
}