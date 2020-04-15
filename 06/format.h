#pragma once
#include <iostream>
#include <sstream>

template <typename Head>
std::stringstream argument(int i, Head head) {
    if (i == 0) {
        std::stringstream required;
        required << head;
        return required;
    }
    else throw std::runtime_error("Some");    
}


template <typename Head, typename ...Arguments >
std::stringstream argument(int i, Head head, Arguments... args) {
    if (i == 0) {
        std::stringstream  required;
        required << head;
        return  required;
    }
    return argument(i - 1, std::forward<Arguments>(args)...);
}


template <typename ...Arguments>
std::string format(const char* row, Arguments... args) {
    std::string fml = row;
    std::stringstream result;
    int size = fml.size();
    for (int i = 0; i < size; i++) {
        if (fml[i] == '}') throw std::runtime_error("Format error");
        else if (fml[i] == '{') {
            int bck_prn = i + 1;
            std::string format_number = "";
            for (; bck_prn < size; bck_prn++) {
                if (isdigit(fml[bck_prn])) format_number += fml[bck_prn];
                else if (fml[bck_prn] == '}') {
                    i = bck_prn ; // i = bck_prn + 1 in next iteration
                    break;
                }
                else throw std::runtime_error("Format argument number error");
            }
            if (!format_number.size()) throw std::runtime_error("There is nothing argument id");
            int argument_id = stoi(format_number);
            try {
                std::stringstream arg_by_id = argument(argument_id, args...);
                result << arg_by_id.str();
            }
            catch (std::runtime_error) {
                throw std::runtime_error("Argument not found");
            }
            
        }
        else result << fml[i]; // Write symbol
    }
    return result.str();
}
