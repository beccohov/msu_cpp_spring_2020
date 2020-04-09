#pragma once
#include <iostream>
#define BASE 100000000
#define DIGITS 9
class BigInt {
public:
    BigInt();
    BigInt(unsigned long long);
    BigInt(const BigInt&);
    ~BigInt();
    BigInt& operator-();
    BigInt operator-(BigInt&);
    BigInt operator+(BigInt&) ;
    BigInt operator+(long long);
    BigInt& operator=(long long);
    BigInt& operator=(const BigInt&);
    bool operator<(BigInt&);
    bool operator<(long long);
    bool operator>(BigInt);
    bool operator>(long long);
    bool operator<=(BigInt&);
    bool operator<=(long long);
    bool operator>=(BigInt&);
    bool operator>=(long long);
    bool operator==(BigInt&);
    bool operator==(long long);
    bool operator!=(BigInt&);
    bool operator!=(long long);
    unsigned long long get_count();
    friend std::ostream& operator<<(std::ostream&,BigInt);
   // friend std::ostream& operator<<(std::ostream&, BigInt);
    BigInt& extend(unsigned long long);
    BigInt abs();
private:
    bool sign;
    unsigned long long* value;
    unsigned long long size;

};