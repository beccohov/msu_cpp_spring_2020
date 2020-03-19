#pragma once
#include <vector>
#include <string>
class Tokenizer {    
public:
        using OnFindStrToken = void(*)(const std::string tkn);
        using OnFindNumToken = void(*)(const int tkn);
        using OnStart = void(*)(class Tokenizer*); //Callback, signature may vary
        using OnEnd = void(*)(class Tokenizer*);//Callback, signature may vary
        Tokenizer(OnFindStrToken,OnFindNumToken,OnStart,OnEnd); //Init        
        void tokenize(const std::string&);
        void defineTokenType(const std::string&);
private:
        const std::string delimiters;
        OnFindNumToken int_cb;
        OnFindStrToken str_cb;
        OnStart start_cb;
        OnEnd end_cb;
        size_t start_from = 0;
};