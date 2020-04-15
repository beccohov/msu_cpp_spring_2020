#pragma once
#include <iostream>
const unsigned long long  BASE = 100000000;
const unsigned long long DIGITS = 9;
class BigInt {
public:
    BigInt();
    BigInt(unsigned long long);
    BigInt(const BigInt&);
    ~BigInt();
    BigInt operator-() const;
    BigInt operator-(const BigInt) const;
    BigInt operator+(const BigInt) const ;
    BigInt operator+(const long long) const;
    BigInt operator=(long long);
    BigInt operator=(const BigInt);
    bool operator<(const BigInt) const;
    bool operator<(const long long);
    bool operator>(const BigInt);
    bool operator>(const long long);
    bool operator<=(const BigInt);
    bool operator<=(const long long);
    bool operator>=(const BigInt);
    bool operator>=(long long);
    bool operator==(const BigInt);
    bool operator==(const long long);
    bool operator!=(const BigInt);
    bool operator!=(const long long);
    unsigned long long get_count() const;
    friend std::ostream& operator<<(std::ostream&,BigInt);
   // friend std::ostream& operator<<(std::ostream&, BigInt);
    BigInt& extend(unsigned long long);
    BigInt abs() const;
private:
    bool sign;
    unsigned long long* value;
    unsigned long long size;

};