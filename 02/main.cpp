#include <iostream>
#include "tokenizer.h"
#include <assert.h>
using namespace std;
void on_start(Tokenizer* t) {
    cout << "Callback In the start of method  successful!\n";
    assert(t != NULL); //test
}
void on_end(Tokenizer* t) {
    cout << "Callback In the end of method successful!\n";
    assert(t != NULL); //test
}
void on_str(const std::string str) {
    cout << "Processor successful! Got:\n";
    cout << str;
    cout << "\n";
}
void on_num(const int num) {
    cout << "Processor successful! Got:\n";
    cout << num;
    cout << "\n";
}
int main() {
    Tokenizer tokenizer(on_str,on_num,on_start,on_end);
    string example = "Hello\n42\tWorld!";
    tokenizer.tokenize(example);    
    cout << "All tests  passed\n";
    return 0;
}