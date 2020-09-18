//
// Created by astrid on 8/18/20.
//

#include "bf.hpp"
#include <immintrin.h>
#include <xmmintrin.h>
#include <vector>

#define BINARY_OP_ARGS short exa, long mta, short exb, long mtb

using namespace bigfloat;

union ieee754_float {
    float value;
    unsigned int bits;
    struct {
        unsigned int mantissa : 23;
        unsigned short exponent : 8;
        bool sign : 1;
    };
};

union ieee754_double {
    double value;
    unsigned long bits;
    struct {
        unsigned long mantissa : 52;
        unsigned short exponent : 11;
        bool sign : 1;
    };
};

bf getBf(short exa, short exb, __int128_t result);

inline int abs_count_zero(long l) {
    return __builtin_clzl(l >= 0 ? l : -l);
}

bf::bf() : mantissa(0), exponent(0) {

}

bf::bf(short exponent, long mantissa) :
        mantissa(mantissa),
        exponent(exponent)
{ }

bf::bf(double x) {
    ieee754_double d = {.value = x};
    if (x == 0.0 || x == -0.0) {
        mantissa = 0;
        exponent = 0;
    } else {
        auto mt = (((unsigned long)d.mantissa << 10) | (1UL << 62));
        mantissa = d.sign ? -mt : mt;
        exponent = (short)d.exponent - 1023;
    }
}

bf::bf(int x) : bf(double(x)) {

}

bf::bf(std::string x) {

}

bf::bf(bf_packed x) {
    mantissa = x.mantissa;
    exponent = x.exponent;
}

bf::operator bf_packed() const {
    return bf_packed{
        .mantissa = mantissa,
        .exponent = exponent,
    };
}

bf::operator double() const {
    if (is_nan()) {
        return std::numeric_limits<double>::quiet_NaN();
    }
    if (is_zero()) {
        return 0.0;
    }
    if (is_inf()) {
        return std::numeric_limits<double>::infinity() * exponent;
    }

    ieee754_double d;
    d.exponent = static_cast<unsigned short>(exponent + 1023);

    if (mantissa >= 0) {
        d.mantissa = static_cast<unsigned long>(mantissa >> 10);
        d.sign = false;
    } else {
        auto abs_mt = -mantissa;
        d.mantissa = static_cast<unsigned long>(abs_mt >> 10);
        d.sign = true;
    }
    return d.value;
}

bf bf::operator+() const {
    return *this;
}

bf bf::operator-() const {
    return bf(exponent, -mantissa);
}

inline bf add_impl(BINARY_OP_ARGS) {
    // Shift to align decimal points
    mtb >>= exa - exb;

    // Same signs?
    if ((mta ^ mtb) >= 0) {
        // Perform addition
        long mto;

        // Overflow handling
        if (__builtin_add_overflow(mta, mtb, &mto)){
            if (mto <= 0) {
                mto = (mto < 0 ? (unsigned long) mto : mto) >> 1;
            }
            mto |= (1L << 62);
            short exo = exa + 1;
            return bf(exo, mto);
        }
        return bf(exa, mto);
    } else {
        // Perform addition (actually subtraction)
        long mto = mta + mtb;
        if (mto == 0) {
            return 0;
        }

        // Count number of leading zeros
        const int shift_amount = abs_count_zero(mto) - 1;
        mto <<= shift_amount;
        short exo = exa - shift_amount;
        return bf(exo, mto);
    }
}

inline bf sort_add_impl(BINARY_OP_ARGS) {
    if (exa == exb && mta == mtb)  // doubling case. takes care of -1 + -1
        return bf(exa + 1, mta);
    if (exa > exb)
        return add_impl(exa, mta, exb, mtb);
    return add_impl(exb, mtb, exa, mta);
}

bf bf::operator+(const bf &other) const {
    return sort_add_impl(exponent, mantissa, other.exponent, other.mantissa);
}

void bf::operator+=(const bf &other) {
    *this = *this + other;
}

bf bf::operator-(const bf &other) const {
    return sort_add_impl(exponent, mantissa, other.exponent, -other.mantissa);
}

inline bf mult_impl(short exa, unsigned long mta, short exb, unsigned long mtb) {
    // Multiply mantissas
    unsigned __int128 mul = (unsigned __int128)((unsigned long)mta << 1) * (unsigned __int128)((unsigned long)mtb << 1);

    if (mul >> 127) {
        // No leading zeros
        unsigned long mto = mul >> 65;
        int exo = exa + exb + 1;  // Bias - 1

        return bf(exo, mto);
    } else {
        // Single leading zero
        unsigned long mto = mul >> 64;
        int exo = exa + exb;  // Bias

        return bf(exo, mto);
    }
}

bf bf::operator*(const bf &other) const {
    if (is_zero() || other.is_zero()) return 0;
    auto exa = exponent;
    auto exb = other.exponent;
    auto mta = mantissa;
    auto mtb = other.mantissa;

    auto sign = ((mta < 0) << 1) | (mtb < 0);
    switch (sign) {
        case 0b00:
            return mult_impl(exa, mta, exb, mtb);
        case 0b01:
            return -mult_impl(exa, mta, exb, -mtb);
        case 0b10:
            return -mult_impl(exa, -mta, exb, mtb);
        case 0b11:
            return mult_impl(exa, -mta, exb, -mtb);
    }
}

void bf::operator*=(const bf &other) {

}

inline bf div_impl(short exa, unsigned long mta, short exb, unsigned long mtb) {
    // Divide mantissas
    __int128 result = ((__int128)mta << 64) / mtb;

    // Extract leading zeros
    __int128 normalized_result = result >= 0 ? result : -result;
    long normalized_result_upper = (unsigned __int128)normalized_result >> 64;
    int leading_zeros = normalized_result_upper
                    ? __builtin_clzl(normalized_result_upper)
                    : 64 + __builtin_clzl(normalized_result);

    // Perform shifting
    int shift_amount = 65 - leading_zeros;
    long mto = result >> shift_amount;

    // Subtract and normalize exponents
    const auto exo = exa - exb + shift_amount - 2;  // bias - 1
    return bf(exo, mto);
}

bf bf::operator/(const bf &other) const {
    int zero = (is_zero() << 1) | other.is_zero();
    switch (zero) {
        case 0b00:  // x / y
            return div_impl(exponent, mantissa, other.exponent, other.mantissa);
        case 0b10:  // 0 / y
            return 0;
        case 0b01:  // x / 0
            return bf::inf((mantissa >= 0) ^ (other.mantissa >= 0));
        case 0b11:  // 0 / 0
            return bf::nan((mantissa < 0) ^ (other.mantissa < 0));
    }
}

inline bool lt_impl(const bf &a, const bf &b) {
    if (a.exponent > b.exponent) return false;
    if (a.exponent < b.exponent) return true;
    return a.mantissa < b.mantissa;
}

inline bool lte_impl(const bf &a, const bf &b) {
    if (a.exponent > b.exponent) return false;
    if (a.exponent < b.exponent) return true;
    return a.mantissa <= b.mantissa;
}

template<bool (*cmp)(const bf&, const bf&)>
inline bool lcmp_impl(const bf &a, const bf &b) {
    int flags = (a.sign() << 1) | b.sign();
    switch (flags) {
        case 0b00:
            return cmp(a, b);
        case 0b01:
            return false;
        case 0b10:
            return true;
        case 0b11:
            return cmp(b, a);
    }
}

bool bf::operator<(const bf &other) const {
    return lcmp_impl<lt_impl>(*this, other);
}

bool bf::operator<=(const bf &other) const {
    return lcmp_impl<lte_impl>(*this, other);
}

bool bf::operator>(const bf &other) const {
    return lcmp_impl<lt_impl>(other, *this);
}

bool bf::operator>=(const bf &other) const {
    return lcmp_impl<lte_impl>(other, *this);
}

bool bf::operator==(const bf &other) const {
    return exponent == other.exponent && mantissa == other.mantissa;
}

bool bf::operator!=(const bf &other) const {
    return false;
}

bool bf::sign() const {
    return mantissa < 0;
}

bool bf::is_zero() const {
    return exponent == 0 && mantissa == 0;
}

bool bf::is_nan() const {
    return (exponent == 32767 || exponent == -32768) && mantissa != 0;
}

bool bf::is_inf() const {
    return (exponent == 32767 || exponent == -32768) && mantissa == 0;
}

bf bf::inf(bool sign) {
    return bf(sign ? 32767 : -32768, 0);
}

bf bf::nan(bool sign) {
    return bf(sign ? 32767 : -32768, 1);
}
