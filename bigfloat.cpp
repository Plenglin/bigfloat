//
// Created by astrid on 8/18/20.
//

#include "bigfloat.hpp"
#include <immintrin.h>
#include <xmmintrin.h>
#include <vector>

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

bigfloat::bigfloat() : sign(false), mantissa(0), exponent(0) {

}

bigfloat::bigfloat(bool sign, unsigned short exponent, unsigned long mantissa) :
        sign(sign),
        mantissa(mantissa),
        exponent(exponent)
{ }

bigfloat::bigfloat(double x) {
    ieee754_double d = {.value = x};
    sign = d.sign;
    if (x == 0.0 || x == -0.0) {
        mantissa = 0;
        exponent = 0;
    } else {
        mantissa = ((unsigned long)d.mantissa << 11) | (1UL << 63);
        exponent = d.exponent;
    }
}

bigfloat::bigfloat(std::string x) {

}

bigfloat::bigfloat(bigfloat_packed x) {
    sign = x.sign;
    mantissa = x.mantissa;
    exponent = x.exponent;
}

bigfloat::operator bigfloat_packed() const {
    return bigfloat_packed{
        .mantissa = mantissa,
        .sign = sign,
        .exponent = exponent,
    };
}

bigfloat::operator double() const {
    if (is_nan()) {
        return std::numeric_limits<double>::quiet_NaN();
    }

    ieee754_double d;
    d.mantissa = static_cast<unsigned long>(mantissa >> 11);
    d.exponent = static_cast<unsigned short>(exponent);
    d.sign = sign;
    return d.value;
}

// Adds a and b, assuming that a's exponent > b's exponent. We're using this complicated
// template system to make the compiler compile away the flags so we only have to do a
// single big jump table at the beginning, minimizing branches.
template <bool adding>
inline bigfloat add_impl(bool sa, int exa, unsigned long mta, int exb, unsigned long mtb) {
    // Shift to align decimal points
    mtb >>= exa - exb;

    // Invert if subtracting
    if (!adding) {
        mtb = -mtb;
    }

    // Perform addition
    unsigned long mto = mta + mtb;

    // Overflow handling
    unsigned short exo = exa;
    if (!adding) {
        int leading_zeros = __builtin_clzl(mto);
        mto <<= leading_zeros;
        exo -= leading_zeros;
    } else if (mto < mta) {
        exo++;
        mto >>= 1;
        mto |= (1UL << 63);
    }
    return bigfloat(sa, exo, mto);
}

#define FLAG_ADDITION 4
#define FLAG_A_GTE_B 2
#define FLAG_DIFF_SIGNS 1

template <bool calling_addition>
inline bigfloat norm_sort_signs_impl(bool sa, int exa, unsigned long mta, bool sb, int exb, unsigned long mtb) {
    // Doing it with a switch statement shaves off about 7ns

    int flags = sa != sb ? FLAG_DIFF_SIGNS : 0;
    flags |= exa >= exb ? FLAG_A_GTE_B : 0;
    if (calling_addition)
        flags |= FLAG_ADDITION;

    switch (flags) {
        case FLAG_ADDITION | FLAG_A_GTE_B | FLAG_DIFF_SIGNS:
            return add_impl<false>(sa, exa, mta, exb, mtb);
        case FLAG_ADDITION | FLAG_A_GTE_B:
            return add_impl<true>(sa, exa, mta, exb, mtb);
        case FLAG_ADDITION | FLAG_DIFF_SIGNS:
            return add_impl<false>(sb, exb, mtb, exa, mta);
        case FLAG_ADDITION:
            return add_impl<true>(sb, exb, mtb, exa, mta);
        case FLAG_A_GTE_B | FLAG_DIFF_SIGNS:
            return add_impl<true>(sa, exa, mta, exb, mtb);
        case FLAG_A_GTE_B:
            return add_impl<false>(sa, exa, mta, exb, mtb);
        case FLAG_DIFF_SIGNS:
            return add_impl<true>(!sb, exb, mtb, exa, mta);
        case 0:
            return add_impl<false>(!sb, exb, mtb, exa, mta);
    }
    throw std::exception();
}

template <bool calling_addition>
inline bigfloat add_impl_deconstruct(const bigfloat &a, const bigfloat &b) {
    return norm_sort_signs_impl<calling_addition>(
            a.sign,
            a.exponent,
            a.mantissa,
            b.sign,
            b.exponent,
            b.mantissa
    );
}

bigfloat bigfloat::operator+(const bigfloat &other) const {
    return add_impl_deconstruct<true>(*this, other);
}

bigfloat bigfloat::operator+=(const bigfloat &other) {
    bigfloat result = *this + other;
    sign = result.sign;
    exponent = result.exponent;
    mantissa = result.mantissa;
}

bigfloat bigfloat::operator-(const bigfloat &other) const {
    return add_impl_deconstruct<false>(*this, other);
}

inline bigfloat mult_impl(bool sa, int exa, unsigned long mta, bool sb, int exb, unsigned long mtb) {
    // Multiply mantissas
    unsigned __int128 mul = (unsigned __int128)mta * (unsigned __int128)mtb;

    // Extract leading zeros
    unsigned long result_upper = mul >> 64;
    int leading_zeros = __builtin_clzl(result_upper);

    // Normalize exponent and mantissa
    unsigned long mto = mul >> (64 - leading_zeros);
    int exo = exa + exb - leading_zeros - 1022;  // Bias - 1

    return bigfloat(sa ^ sb, exo, mto);
}

bigfloat bigfloat::operator*(const bigfloat &other) const {
    if (is_zero() || other.is_zero()) {
        return bigfloat(sign ^ other.sign, 0, 0);
    }
    return mult_impl(sign, exponent, mantissa, other.sign, other.exponent, other.mantissa);
}

inline bigfloat div_impl(bool sign, int exa, unsigned long mta, int exb, unsigned long mtb) {
    // Divide mantissas
    unsigned __int128 result = ((unsigned __int128)mta << 64) / (unsigned __int128)mtb;

    // Subtract exponents
    int exo = exa - exb;

    // Extract leading zeros
    unsigned long result_upper = result >> 64;
    unsigned long mto;
    if (result_upper) {
        // There is upper stuff
        int leading_zeros = __builtin_clzl(result_upper);
        mto = result >> (64 - leading_zeros);

        // Subtract and normalize exponents
        exo += leading_zeros + (1024 - 64);  // bias + 1 - 64
    } else {
        // There is no upper stuff
        int leading_zeros = __builtin_clzl((unsigned long) result);
        mto = result << leading_zeros;

        // Subtract and normalize exponents
        exo += -leading_zeros + 1022;  // bias + 1 - 64
    }

    return bigfloat(sign, exo, mto);
}

bigfloat bigfloat::operator/(const bigfloat &other) const {
    bool so = sign ^ other.sign;
    int zero = (is_zero() << 1) | other.is_zero();
    switch (zero) {
        case 0b00:  // x / y
            return div_impl(so, exponent, mantissa, other.exponent, other.mantissa);
        case 0b10:  // 0 / y
            return bigfloat(so, 0, 0);  // signed zero
        case 0b01:  // x / 0
            return bigfloat::inf(so);
        case 0b11:  // 0 / 0
            return bigfloat::nan(!so);
    }
    return bigfloat();
}

bool bigfloat::operator==(const bigfloat &other) const {
    return sign == other.sign && mantissa == other.mantissa && exponent == other.exponent;
}

bigfloat bigfloat::operator-() const {
    return bigfloat(!sign, mantissa, exponent);
}

bigfloat bigfloat::operator+() const {
    return *this;
}

bool bigfloat::is_zero() const {
    return !(mantissa || exponent);
}

bool bigfloat::is_nan() const {
    return exponent == (unsigned short)-1 && mantissa;
}

bigfloat bigfloat::inf(bool sign) {
    return bigfloat(sign, -1, 0);
}

bigfloat bigfloat::nan(bool sign) {
    return bigfloat(sign, -1, 1);
}

short bigfloat::unbiased_exponent() const {
    return (short)(exponent - 1023);
}

inline bool le_impl(const bigfloat &a, const bigfloat &b) {
    return a.exponent < b.exponent || a.mantissa < b.mantissa;
}

inline bool leq_impl(const bigfloat &a, const bigfloat &b) {
    return a.exponent <= b.exponent || a.mantissa <= b.mantissa;
}

template<bool (*cmp)(const bigfloat&, const bigfloat&), bool mp_result>
inline bool cmp_impl(const bigfloat &a, const bigfloat &b) {
    int flags = (a.sign << 1) | b.sign;
    switch (flags) {
        case 0b00:
            return cmp(a, b);
        case 0b01:
            return !mp_result;
        case 0b10:
            return mp_result;
        case 0b11:
            return cmp(b, a);
    }
}

bool bigfloat::operator<(const bigfloat &other) const {
    return cmp_impl<le_impl, true>(*this, other)
}

bool bigfloat::operator>(const bigfloat &other) const {
    return cmp_impl<leq_impl, true>(*this, other)
}

std::ostream &operator<<(std::ostream &os, bigfloat x) {
    std::vector<char> digits;
    auto ten = bigfloat(1);
    while (x > ten) {

    }
    auto remainder = x;

    if (x.sign) {
        os << "-";
    }
    return os;
}
