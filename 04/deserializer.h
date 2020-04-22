#pragma once
#include <string.h>
#include "serializer.h"
class Deserializer {
    static constexpr char separator = ' ';
public:
    explicit Deserializer(std::istream& in) : instream(in) {
    }
    template <typename Type>
    Errors load(Type& object_to_save) {
        return object_to_save.deserialize(*this);
    };
    template <typename... Types>
    Errors operator()(Types&... args) {
        //process(x);
        return process(args...);
    }
private:
    std::istream &instream;
    template<typename Type>
    Errors process(Type &value) {
        return load_data(value);
    }
    template<typename Type, typename... Types>
    Errors process(Type &value, Types &&... args) {
        Errors res = load_data(value);
        if (res == Errors::Error)
            return Errors::Error;
        return process(std::forward<Types>(args)...);

    }
    template<typename Type>
    Errors load_data(Type& value) {
        std::string variable;
        instream >> variable;
        if (variable.find_first_not_of("0123456789") != std::string::npos)
            return Errors::Error;
        value = std::stoi(variable);
        return Errors::NoError;
    }
    template<>
    Errors load_data(bool& value) {
        std::string text;
        instream >> text;
        if (text == "true") value = true;
        else if (text == "false") value = false;
        else return Errors::Error;
        return Errors::NoError;
    }
    
};