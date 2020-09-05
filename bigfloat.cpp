//
// Created by astrid on 8/18/20.
//

#include "bigfloat.hpp"
#include "immintrin.h"


bigfloat::bigfloat() : sign(false), mantissa(0), exponent(0) {

}

bigfloat::bigfloat(bool sign, unsigned char exponent, unsigned long mantissa) :
        sign(sign),
        mantissa(mantissa),
        exponent(exponent)
{ }

bigfloat::bigfloat(double x) {
    ieee754_double d = {.d = x};
    sign = d.sign;
    mantissa = d.mantissa << 12;
    exponent = (d.exponent - (1023 << 4));
}

bigfloat::bigfloat(float x) {
    ieee754_float f = {.f = x};
    sign = f.sign;
    mantissa = (unsigned long)f.mantissa << 40;
    exponent = f.bits >> 23;
}

bigfloat::operator float() const {
    ieee754_float f;
    f.mantissa = static_cast<unsigned int>(mantissa >> 40);
    f.exponent = static_cast<short>(exponent);
    f.sign = sign;
    return f.f;
}

bigfloat::operator double() const {
    return 0;
}

// Adds a and b, assuming that a's exponent > b's exponent. We're using this complicated
// template system to hopefully make the compiler compile away the flags so we only have to do a single check
// at the beginning, minimizing branches.
template <bool invert_b, bool sign_same, bool sa>
inline bigfloat add_impl(unsigned long mta, int exa, unsigned long mtb, int exb) {
    int shift = exa - exb;

    // Are we subtracting?
    if (invert_b ^ !sign_same) {
        mtb = -mtb;
    }

    // Add on the implicit 1
    mtb >>= shift;
    mtb |= (1UL << (63 - shift));

    unsigned char exo = exa;

    // Perform addition
    unsigned long mto = mta + mtb;

    if (invert_b ^ !sign_same) {
        // Subtracting and underflow
        mto = -mto;
    } else if (mto & (1UL << 63)) {
        // Adding and overflow
        exo++;
        mto &= ((unsigned long)(-1) >> 1);
        mto >>= 1;
    }


    return bigfloat(false, exo, mto);
}

template <bool invert_b>
inline bigfloat add_impl(const bigfloat a, const bigfloat b) {
    if (a.sign) {
        if (b.sign) {
            return add_impl<invert_b, true, true>(a.mantissa, a.exponent, b.mantissa, b.exponent);
        }
        return add_impl<invert_b, false, true>(a.mantissa, a.exponent, b.mantissa, b.exponent);
    }
    if (b.sign) {
        return add_impl<invert_b, false, false>(a.mantissa, a.exponent, b.mantissa, b.exponent);
    }
    return add_impl<invert_b, true, false>(a.mantissa, a.exponent, b.mantissa, b.exponent);
}

bigfloat bigfloat::operator+(const bigfloat &other) const {
    if (exponent < other.exponent) {
        return add_impl<true>(other, *this);
    } else {
        return add_impl<false>(*this, other);
    }
}

bigfloat bigfloat::operator-(const bigfloat &other) {
    if (exponent < other.exponent) {
        return add_impl<true>(other, *this);
    } else {
        return add_impl<true>(*this, other);
    }
}

bigfloat bigfloat::operator*(const bigfloat &other) {
    bigfloat out;
    return out;
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

bigfloat::bigfloat(std::string x) {

}


std::ostream &operator<<(std::ostream &os, bigfloat x) {
    if (x.sign) {
        os << "-";
    }
    os << "1." << x.mantissa << "e" << (int)x.exponent;
    return os;
}
