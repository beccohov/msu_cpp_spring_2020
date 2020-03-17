#pragma once
#include <vector>
#include <string>
typedef struct { // Store string segment
    size_t begin;
    size_t end;
} TokenString;
typedef struct { // Store string segment
    size_t begin;
    size_t end;
} TokenNumber;
typedef struct { // Store delimiter segment
    size_t begin;
    size_t length;
} Delimiter;
class Tokenizer {    
public:
        Tokenizer(const std::vector<std::string>&); //Init
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
        const std::vector<std::string> delimiters;
        Delimiter findDelimiter(const std::string&,size_t);
        void Collect(const std::string&, size_t, size_t, OnFindStrToken,OnFindNumToken);
};