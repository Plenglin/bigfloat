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