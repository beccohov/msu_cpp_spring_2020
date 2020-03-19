#include "tokenizer.h"
#include <string>
#include <vector>
using namespace std;   

Tokenizer::Tokenizer(OnFindStrToken strcb, OnFindNumToken intcb, OnStart startcb, OnEnd endcb) : delimiters(" ""\n""\t")
{
    str_cb = strcb;
    int_cb = intcb;
    start_cb = startcb;
    end_cb = endcb;
}
void Tokenizer::defineTokenType(const std::string &token) // Call function in order to the token type
{
    bool number = true;
    for (auto symb : token) {
        if (!isdigit(symb)) {
            number = false;
            break;
        }
    }
    if (number) int_cb(atoi(token.c_str()));
    else str_cb(token);
}
void Tokenizer::tokenize(const std::string &str)
{
    size_t found = 0;
    start_cb(this); //call
    while (found != std::string::npos && (str.length() != 0)) {
        found = str.find_first_of(delimiters,start_from);
        size_t sublength = found == std::string::npos ? str.length() - start_from : found - start_from;
        std::string token = str.substr(start_from, sublength);
        start_from = found + 1;
        defineTokenType(token);
    }
    end_cb(this); //call
}