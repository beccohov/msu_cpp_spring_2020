#pragma once
#include <iostream>
#include <inttypes.h>
enum class Errors {
    NoError,
    Error
};
class Serializer {
    static constexpr char separator = ' ';
public:
    explicit Serializer(std::ostream& out) :outstream(out)
    {
    }
    template<typename Type>
    Errors save(Type object_to_save) {
        return object_to_save.serialize(*this);
    };
    template <typename... Types>
    Errors operator()(Types... args) {
        return Serializer::process(args...);
    }
private:
    std::ostream& outstream;
    template<typename Type>
    Errors put_to_stream(Type argument) {
        outstream << argument << separator;
        return Errors::NoError;
    }
    template<>
    Errors put_to_stream<bool>(bool argument) { //specialization
        if (argument) outstream << "true" << separator;
        else outstream << "false" << separator;
        return Errors::NoError;
    }
    template <typename Type>
    Errors process(Type variable) {
        if (typeid(Type) != typeid(uint64_t) && typeid(Type) != typeid(bool))
            return Errors::Error;
        put_to_stream(variable);
        return Errors::NoError;
    }
    template<typename Type,typename... Types>
    Errors process(Type arg,Types... args) {
        if (typeid(Type) != typeid(uint64_t) && typeid(Type) != typeid(bool))
            return Errors::Error;
        put_to_stream(arg);
        return process(std::forward<Types>(args)...);
    }
};