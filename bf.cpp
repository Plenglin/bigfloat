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

inline bf mult_impl(BINARY_OP_ARGS) {
    // Multiply mantissas
    __int128 mul = (__int128)mta * (__int128)mtb;
    long upper = mul >> 64;
    int less_shift = abs_count_zero(upper) - 1;

    long mto = mul >> (64 - less_shift);
    short exo = exa + exb - less_shift + 2;

    return bf(exo, mto);
}

bf bf::operator*(const bf &other) const {
    if (is_zero() || other.is_zero()) return 0;
    return mult_impl(exponent, mantissa, other.exponent, other.mantissa);
}

void bf::operator*=(const bf &other) {

}

template <bool result_is_positive>
inline bf div_helper_upper_nonzero(short exa, short exb, __int128 result, long result_upper) {
    int shift_amount = 65 - __builtin_clzl(result_is_positive ? result_upper : -result_upper);
    long mto = result >> shift_amount;

    // Subtract and normalize exponents
    const auto exo = exa - exb + shift_amount - 2;  // bias - 1
    return bf(exo, mto);
}

template <bool result_is_positive>
inline bf div_helper_upper_nonzero(short exa, short exb, __int128 result) {
    long mto = result >> 1;

    // Subtract and normalize exponents
    const auto exo = exa - exb - 1;  // bias - 1
    return bf(exo, mto);
}

template <bool result_is_positive>
inline bf div_helper_upper_zero(short exa, short exb, __int128 result) {
    long result_lower = result;
    int leading_zeros = __builtin_clzl(result_is_positive ? result_lower : -result_lower);
    if ((leading_zeros == 0)) {
        return div_helper_upper_nonzero<result_is_positive>(exa, exb, result);
    }
    int shift_amount = leading_zeros - 1;
    long mto = result << shift_amount;

    // Subtract and normalize exponents
    const auto exo = exa - exb - shift_amount;
    return bf(exo, mto);
}

inline bf div_impl(BINARY_OP_ARGS) {
    // Divide mantissas
    __int128 result = ((__int128)mta << 64) / mtb;

    // Extract leading zeros
    long result_upper = result >> 64;

    if (result_upper == 0) {
        // There is no upper stuff and the result is positive
        return div_helper_upper_zero<true>(exa, exb, result);
    } else if (result_upper == -1) {
        // There is no upper stuff and the result is negative
        return div_helper_upper_zero<false>(exa, exb, result);
    } else {
        // There is upper stuff
        if ((long)result >= 0) {
            return div_helper_upper_nonzero<true>(exa, exb, result, result_upper);
        } else {
            return div_helper_upper_nonzero<false>(exa, exb, result, result_upper);
        }
    }
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
