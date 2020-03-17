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
void on_str(const TokenString tok) {
    cout << "Processor successful!\n";
}
void on_num(const TokenNumber tok) {
    cout << "Processor successful!\n";
}
int main() {
    Tokenizer tokenizer({" ","\n","\t"});
    string example = "Hello\n42\tWorld!";
    tokenizer.tokenize(example,on_str,on_num,on_start,on_end);
    vector<TokenString> tokens_str = tokenizer.getStrTokens();
    assert(tokens_str[0].begin == 0);
    assert(tokens_str[0].end == 5);
    assert(tokens_str[1].begin == 9);
    assert(tokens_str[1].end == 15);
    vector<TokenNumber> tokens_num = tokenizer.getNumTokens();    
    assert(tokens_num[0].begin == 6);
    assert(tokens_num[0].end == 8);
    cout << "All tests  passed\n";
    return 0;
}