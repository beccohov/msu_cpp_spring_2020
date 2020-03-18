#pragma once
#include <vector>
#include <string>
struct TokenString { // Store string segment
    size_t begin;
    size_t end;
};
struct TokenNumber { // Store string segment
    size_t begin;
    size_t end;
};
struct Delimiter { // Store delimiter segment
    size_t begin;
    size_t length;
};
class Tokenizer {    
public:
        Tokenizer(); //Init
        std::vector<TokenString> getStrTokens();
        std::vector<TokenNumber> getNumTokens();
        using OnFindStrToken = void(*)(const TokenString tkn);
        using OnFindNumToken = void(*)(const TokenNumber tkn);
        using OnStart = void(*)(class Tokenizer*); //Callback, signature may vary
        using OnEnd = void(*)(class Tokenizer*);//Callback, signature may vary
        void tokenize(const std::string&,OnFindStrToken,OnFindNumToken,OnStart,OnEnd);
private:
        std::vector<TokenString> tokens_string; //All string-tokens in string
        std::vector<TokenNumber> tokens_number;
        const std::string delimiters;
        Delimiter findDelimiter(const std::string&,size_t);
        void Collect(const std::string&, size_t, size_t, OnFindStrToken,OnFindNumToken);
};