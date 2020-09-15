//
// Created by astrid on 8/18/20.
//

#include "bf.hpp"
#include <immintrin.h>
#include <xmmintrin.h>
#include <vector>

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

bf add_impl(short exa, long mta, short exb, long mtb) {
    // Shift to align decimal points
    mtb >>= exa - exb;

    // Same signs?
    if ((mta ^ mtb) >= 0) {
        // Perform addition
        long mto;

        // Overflow handling
        if (__builtin_add_overflow(mta, mtb, &mto)){
            if (mto > 0) {
                mto |= (1L << 62);
            } else {
                if (mto < 0) {
                    mto = ((unsigned long)mto >> 1) | (1L << 62);
                } else {
                    mto = (mto >> 1) | (1L << 62);
                }
            }
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

        if (mto > 0) {
            int shift_amount = __builtin_clzl(mto) - 1;
            mto <<= shift_amount;
            short exo = exa - shift_amount;
            return bf(exo, mto);
        } else {
            int shift_amount = __builtin_clzl(-mto) - 1;
            mto <<= shift_amount;
            short exo = exa - shift_amount;
            return bf(exo, mto);
        }
    }
}

bf bf::operator+(const bf &other) const {
    if (exponent > other.exponent)
        return add_impl(exponent, mantissa, other.exponent, other.mantissa);
    return add_impl(other.exponent, other.mantissa, exponent, mantissa);
}

void bf::operator+=(const bf &other) {

}

bf bf::operator-(const bf &other) const {
    return bf();
}

bf bf::operator*(const bf &other) const {
    return bf();
}

void bf::operator*=(const bf &other) {

}

bf bf::operator/(const bf &other) const {
    return bf();
}

bool bf::operator<(const bf &other) const {
    return false;
}

bool bf::operator>(const bf &other) const {
    return false;
}

bool bf::operator<=(const bf &other) const {
    return false;
}

bool bf::operator>=(const bf &other) const {
    return false;
}

bool bf::operator==(const bf &other) const {
    return false;
}

bool bf::operator!=(const bf &other) const {
    return false;
}

bool bf::is_zero() const {
    return exponent == 0 && mantissa == 0;
}

bool bf::is_nan() const {
    return false;
}

bf bf::inf(bool sign) {
    return bf();
}

bf bf::nan(bool sign) {
    return bf();
}
