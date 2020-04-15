#include "BigInt.h"
#include <iomanip>
#include <inttypes.h>
#include <cstring>
const int INITIAL = 9;
BigInt::BigInt()
{
    sign = false;
    value = (unsigned long long*)calloc(INITIAL,sizeof(long long));
    size = INITIAL;
}
BigInt::BigInt(unsigned long long number)
{   
    sign = number < 0;
    value = (unsigned long long*)calloc(INITIAL, sizeof(long long));
    size = INITIAL;
    unsigned long long less = number % BASE;
    unsigned long long other = number / BASE;
    unsigned long long higher = other / BASE;
    other %= BASE;
    for (int i = 0; i < size; i++) value[i] = 0;
    value[0] = less;
    value[1] = other;
    value[2] = higher;
}
BigInt::BigInt(const BigInt &x)
{
    this->value =(unsigned long long*)calloc(x.size , sizeof(long long));
    memcpy(this->value, x.value, x.size*sizeof(long long));
    this->sign = x.sign;
    this->size = x.size;
}
BigInt::~BigInt()
{
    free(value);
}
unsigned long long BigInt::get_count() const
{
    unsigned long long r = 0;
    for (int i = size - 1; i >= 0; i--) {
        if (value[i] == 0) r++;
        else break;
    }
    return size - r;
}
BigInt BigInt::operator-() const
{
    BigInt minus_this = *this;
    minus_this.sign = !sign;
    return minus_this;
}
BigInt  BigInt::operator=(const BigInt  right)
{
    value = (unsigned long long*)realloc(value,right.size * sizeof(long long));
    sign = right.sign;
    size = right.size;
    for (int i = 0; i < size; i++) {
        value[i] = right.value[i];
    }
    return *this;
}
BigInt& BigInt::extend(unsigned long long ext)
{   
    value = (unsigned long long*)realloc(value, (this->size + ext) * sizeof(long long));
    return *this;
}
BigInt BigInt::operator=(const long long number)
{   
    long long n;
    sign = number < 0;
    n = number > 0 ? number : -number;
    unsigned long long less = n % BASE;
    unsigned long long other = n / BASE;
    unsigned long long higher = other / BASE;
    other %= BASE;
    for (int i = 0; i < size; i++) value[i] = 0;
    value[0] = less;
    value[1] = other;
    value[2] = higher;
    return *this;
}
BigInt  BigInt::operator-(const BigInt  right) const
{
    if (sign == right.sign) {
        if (this->abs() > right.abs()) {
            BigInt result = *this;
            for (int i = 0, carry = 0; i < (int)right.size || carry; ++i) {
                result.value[i] -= carry + (i < (int)right.size ? right.value[i] : 0);
                carry = result.value[i] < 0;
                if (carry)
                    result.value[i] += BASE;
            }
            //result.trim();
            return result;
        }
        return -(right - *this);
    }

    return (*this + (-right));
}
BigInt  BigInt::abs()  const
{
    BigInt result = *this;
    result.sign = false;
    return result;
}
BigInt  BigInt::operator+(const BigInt  left) const
{
    if (sign == left.sign) {
        unsigned long long lc = left.get_count(), rc = this->get_count();
        unsigned long long max_size = lc > rc ? lc : rc;
        unsigned long long min_size = lc < rc ? lc : rc;
        BigInt result = left;
        for (int i = 0, carry = 0; i < max_size || carry; ++i) {
            if (i == result.size) result.extend(1);
            result.value[i] += carry + (i < (int)this->size ? this->value[i] : 0);
            carry = result.value[i] >= BASE;
            if (carry) result.value[i] -= BASE;
        }
        return result;
    }
    return (*this - (-left));
}

BigInt BigInt::operator+(const long long x) const
{   
    BigInt number(x);
    return *this + number;
}

std::ostream & operator<<(std::ostream & stream,BigInt integer)
{
    unsigned long long s = integer.get_count();
    if (integer.sign == -1) stream << '-';
    stream << ( s == 0 ? 0 : integer.value[s-1]);
    for (int i = s - 2; i >= 0; --i)
        stream << std::setw(INITIAL) << std::setfill('0') << integer.value[i];
    return stream;
}

bool BigInt::operator>(const BigInt c)
{   
    if (sign > c.sign) return false;
    if (sign < c.sign) return true;
    unsigned long long len1 = this->get_count();
    unsigned long long len2 = c.get_count();
    if (sign) {
        if (len1 != len2)  return len1 < len2;
        if (len1 == 0) return false;
        bool greater = true;
        for (int i = len1 - 1; i >= 0; i--) if (value[i] > c.value[i]) {
            greater = false;
            break;
        }
        return greater;
    }
    if (len1 != len2)  return len1 > len2;
    if (len1 == 0) return false;
    bool greater = true;
    for (int i = len1 - 1; i >= 0; i--) if (value[i] < c.value[i]) {
        greater = false;
        break;
    }
    return greater;
}
bool BigInt::operator>(const long long x)
{
    BigInt number(x);
    return *this > number;
}
bool BigInt::operator<=(const BigInt right)
{ 
    return !(*this > right);
}
bool BigInt::operator<=(const long long x)
{
    BigInt number(x);
    return !(*this > number);
}
bool BigInt::operator>=(const BigInt right)
{
    return !(*this < right);
}
bool BigInt::operator<(const BigInt right) const
{
    BigInt to_cmp = right;
    return to_cmp > *this;
}
bool BigInt::operator<(const long long x)
{
    BigInt number(x);
    return *this < number;
}
bool BigInt::operator>=(const long long x)
{
    return !(*this < x);
}
bool BigInt::operator==(const BigInt  right)
{
    if (sign != right.sign) return false;
    bool r = true;
    unsigned long long len1, len2;
    len1 = this->get_count();
    len2 = right.get_count();
    if (len1 != len2) return false;
    for (int i = 0; i < len1; i++) if (this->value[i] != right.value[i]) {
        r = false;
        break;
    }
    return r;
}
bool BigInt::operator==(const long long x)
{
    BigInt number(x);
    return *this == number;
}
bool BigInt::operator!=(const BigInt  right)
{
    return !(*this == right);
}
bool BigInt::operator!=(const long long x)
{
    return !(*this == x);
}