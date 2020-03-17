#include "tokenizer.h"
#include <string>
#include <vector>
using namespace std;                                                      
Tokenizer::Tokenizer(const std::vector<std::string> & delim) : delimiters(delim)
{   
}
std::vector<TokenString> Tokenizer::getStrTokens()
{
    return this->tokens_string;
}
std::vector<TokenNumber> Tokenizer::getNumTokens()
{
    return this->tokens_number;
}
void Tokenizer::Collect(const std::string &str, size_t start, size_t end, OnFindStrToken on_str, OnFindNumToken on_num)
{
    bool is_num = true;
    for (int i = start; i < end; i++) if (!isdigit(str.at(i))) {
        is_num = false; // It's a string token
        break;
    }
    if (is_num) {
        tokens_number.push_back({ start,end });
        on_num({ start,end }); //Callback
    }
    else {
        tokens_string.push_back({ start,end });
        on_str({ start,end }); //Callback
    }
}
Delimiter Tokenizer::findDelimiter(const std::string & str,size_t start)
{   
    size_t min_pos = str.length();
    size_t length = 0;
    for (auto dlmtr : delimiters) {
        auto position = str.find(dlmtr, start);
        if (position < min_pos) { // save min position
            min_pos = position;
            length = dlmtr.length(); // delimiter length
        }
    }
    return {min_pos,length};
}
void Tokenizer::tokenize(const std::string &str, \
    OnFindStrToken str_tok, OnFindNumToken num_tok, OnStart on_start, OnEnd on_end)
{
    tokens_string.clear();//Clean old data
    tokens_number.clear();//Clean old data
    size_t start = 0, end = 0;
    on_start(this); //call
    while (end != str.length()) {
        auto delimiter = findDelimiter(str, start);
        end = delimiter.begin;
        Collect(str, start, end,str_tok,num_tok); //With callback
        start = end + delimiter.length;
    }
    on_end(this); //call
}