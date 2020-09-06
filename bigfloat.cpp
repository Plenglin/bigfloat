//
// Created by astrid on 8/18/20.
//

#include "bigfloat.hpp"
#include "immintrin.h"


typedef union {
    float value;
    unsigned int bits;
    struct {
        unsigned int mantissa : 23;
        short exponent : 8;
        bool sign : 1;
    };
} ieee754_float;

typedef union {
    double value;
    unsigned long bits;
    struct {
        unsigned long mantissa : 52;
        short exponent : 11;
        bool sign : 1;
    };
} ieee754_double;

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
    mantissa = ((unsigned long)d.mantissa << 11) | (1UL << 63);
    exponent = d.exponent;
}

bigfloat::bigfloat(std::string x) {

}

bigfloat::operator float() const {
    ieee754_float f;
    f.mantissa = static_cast<unsigned int>(mantissa >> 40);
    f.exponent = static_cast<short>(exponent - 1023 + 127);
    f.sign = sign;
    return f.value;
}

bigfloat::operator double() const {
    ieee754_double d;
    d.mantissa = static_cast<unsigned long>(mantissa >> 11);
    d.exponent = static_cast<short>(exponent);
    d.sign = sign;
    return d.value;
}

// Adds a and b, assuming that a's exponent > b's exponent. We're using this complicated
// template system to hopefully make the compiler compile away the flags so we only have to do a single check
// at the beginning, minimizing branches.
template <bool adding>
inline bigfloat add_impl(bool sa, int exa, unsigned long mta, int exb, unsigned long mtb) {
    int shift = exa - exb;

    // Shift to align decimal points
    mtb >>= shift;

    // Invert if subtracting
    if (!adding) {
        mtb = -mtb;
    }

    // Perform addition
    unsigned long mto = mta + mtb;

    // Overflow handling
    if (!adding) {
        int leading_zeros = __builtin_clzl(mto);
        mto <<= leading_zeros;
        unsigned short exo = exa - leading_zeros;

        return bigfloat(sa, exo, mto);
    } else {
        bool carry = mto < mta;
        unsigned short exo = exa + carry;
        mto >>= carry;
        mto |= (1UL << 63);
        return bigfloat(sa, exo, mto);
    }
}

inline bigfloat add_check_signs(bool sa, int exa, unsigned long mta, bool sb, int exb, unsigned long mtb) {
    return sa != sb
        ? add_impl<false>(sa, exa, mta, exb, mtb)
        : add_impl<true>(sa, exa, mta, exb, mtb);
}

inline bigfloat add_sort_exponents(bool sa, int exa, unsigned long mta, bool sb, int exb, unsigned long mtb) {
    return exa >= exb
        ? add_check_signs(sa, exa, mta, sb, exb, mtb)
        : add_check_signs(sb, exb, mtb, sa, exa, mta);
}

template <bool calling_addition>
inline bigfloat add_normalize_signs(const bigfloat &a, const bigfloat &b) {
    return add_sort_exponents(
            a.sign,
            a.exponent,
            a.mantissa,
            b.sign ^ !calling_addition,
            b.exponent,
            b.mantissa
        );
}

bigfloat bigfloat::operator+(const bigfloat &other) const {
    return add_normalize_signs<true>(*this, other);
}

bigfloat bigfloat::operator+=(const bigfloat &other) {
    bigfloat result = *this + other;
    sign = result.sign;
    exponent = result.exponent;
    mantissa = result.mantissa;
}

bigfloat bigfloat::operator-(const bigfloat &other) const {
    return add_normalize_signs<false>(*this, other);
}

inline bigfloat mult_impl(bool s, int ex, unsigned long mt, int i) {
    bool i_sign = (i < 0);
    s ^= i_sign;
    i = i_sign ? -i : i;

    bigfloat acc;
    while (i > 0) {
        if (i & 1) {
            acc += bigfloat(s, ex, mt);
        }
        ex++;
        i >>= 1;
    }

    return acc;
}

inline bigfloat mult_impl(bool sa, int exa, unsigned long mta, bool sb, int exb, unsigned long mtb) {

    return bigfloat();
}

bigfloat operator*(const bigfloat &bf, const int &i) {
    return mult_impl(bf.sign, bf.exponent, bf.mantissa, i);
}

bigfloat operator*(const int &i, const bigfloat &bf) {
    return mult_impl(bf.sign, bf.exponent, bf.mantissa, i);
}

bigfloat bigfloat::operator*(const bigfloat &other) {
    return mult_impl(sign, exponent, mantissa, other.sign, other.exponent, other.mantissa);
}

bigfloat bigfloat::operator/(const bigfloat &other) {
    bigfloat out;
    return out;
}

bool bigfloat::operator==(const bigfloat &other) const {
    return sign == other.sign && mantissa == other.mantissa && exponent == other.exponent;
}

bigfloat bigfloat::operator-() const {
    return bigfloat(!sign, mantissa, exponent);
}

void bigfloat::to_mpfr(mpfr_t rop) {
    mpfr_init2(rop, 63);
    mpfr_set_ui_2exp(rop, mantissa, exponent, MPFR_RNDD);
}

std::ostream &operator<<(std::ostream &os, bigfloat x) {
    if (x.sign) {
        os << "-";
    }
    os << "1." << x.mantissa << "e" << (int)x.exponent;
    return os;
}