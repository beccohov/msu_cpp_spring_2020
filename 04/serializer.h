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
    template <typename Type,typename... Types>
    Errors operator()(Type x, Types... args) {
        return process<Type,Types...>(x,args...);
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
    template <class T>
    struct is_pod
    {
        static constexpr bool value = false;
    };
    template <>
    struct is_pod<uint64_t>
    {
        static constexpr bool value = true;
    };
    template <>
    struct is_pod<bool>
    {
        static constexpr bool value = true;
    };

    template<typename Type >
    Errors process_one(Type variable, typename std::enable_if<!std::is_pod<Type>::value>::type* = nullptr)
    {
        return Errors::Error;
    }
    template<typename Type>
    Errors process_one(Type variable, typename std::enable_if<std::is_pod<Type>::value>::type* = nullptr)
    {
        put_to_stream(variable);
        return Errors::NoError;
    } 
    template<typename Type, typename... Types>
    Errors process(Type arg, Types... args) {
        Errors code = process_one(arg);
        if (code == Errors::Error) return Errors::Error;
        return process(std::forward<Types>(args)...);
    }
    template<typename Type>
    Errors process(Type arg) {
        Errors code =  process_one(arg);
        return code;
    }
};