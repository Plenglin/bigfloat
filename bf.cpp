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

inline bf add_impl(BINARY_OP_ARGS) {
    // Shift to align decimal points
    mtb >>= exa - exb;

    // Different signs?
    if ((bool) ((unsigned long) (mta ^ mtb) >> 63)) {
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
    } else {
        // Perform addition
        long mto;

        // Overflow handling
        if (__builtin_add_overflow(mta, mtb, &mto)) {
            if (mto <= 0) {
                mto = (unsigned long) mto >> 1;
            }
            mto |= (1L << 62);
            short exo = exa + 1;
            return bf(exo, mto);
        }
        return bf(exa, mto);
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

bf bf::operator-(const bf &other) const {
    return sort_add_impl(exponent, mantissa, other.exponent, -other.mantissa);
}

inline bf mult_impl(short exa, unsigned long mta, short exb, unsigned long mtb) {
    // Multiply mantissas
    unsigned __int128 mul = (unsigned __int128)((unsigned long)mta << 1) * (unsigned __int128)((unsigned long)mtb << 1);
    unsigned long upper = mul >> 64;

    int sign = upper >> 63;
    unsigned long mto = upper >> sign;
    int exo = exa + exb + sign;  // Bias - 1

    return bf(exo, mto);
}

bf bf::operator*(const bf &other) const {
    if (is_zero() || other.is_zero()) return 0;
    auto exa = exponent;
    auto exb = other.exponent;
    auto mta = mantissa;
    auto mtb = other.mantissa;

    auto sign = (((unsigned long)mta >> 63) << 1) | ((unsigned long)mtb >> 63);
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

inline bf div_impl(short exa, unsigned long mta, short exb, unsigned long mtb) {
    // Divide mantissas
    auto dividend = (unsigned __int128)mta << 65;
    unsigned __int128 result = dividend / mtb;

    // First, we shift such that the MSB is at bit 63 of the long. This makes the else branch simpler.

    // Extract leading zeros
    unsigned long result_upper = result >> 64;
    unsigned long mto;
    int exo = exa - exb;
    if (result_upper) {
        // There is upper stuff
        int leading_zeros = __builtin_clzl(result_upper);
        int shift_amount = 64 - leading_zeros;
        mto = result >> shift_amount;

        // Subtract and normalize exponents
        exo += shift_amount - 2;
    } else {
        // There is no upper stuff
        int leading_zeros = __builtin_clzl((unsigned long) result);
        mto = result << leading_zeros;

        // Subtract and normalize exponents
        exo -= leading_zeros;
    }

    // Before constructing the float, we will shift the MSB to its proper place (bit 62).
    mto >>= 1;
    return bf(exo, mto);
}

inline bf normalize_sign_div(short exa, long mta, short exb, long mtb) {
    int sign = ((mta < 0) << 1) | (mtb < 0);
    switch (sign) {
        case 0b00:
            return div_impl(exa, mta, exb, mtb);
        case 0b01:
            return -div_impl(exa, mta, exb, -mtb);
        case 0b10:
            return -div_impl(exa, -mta, exb, mtb);
        case 0b11:
            return div_impl(exa, -mta, exb, -mtb);
    }
}

bf bf::operator/(const bf &other) const {
    int zero = (is_zero() << 1) | other.is_zero();
    switch (zero) {
        case 0b00: // x / y
            return normalize_sign_div(exponent, mantissa, other.exponent, other.mantissa);
        case 0b10:  // 0 / y
            return 0;
        case 0b01:  // x / 0
            return bf::inf((mantissa >= 0) ^ (other.mantissa >= 0));
        case 0b11:  // 0 / 0
            return bf::nan((mantissa < 0) ^ (other.mantissa < 0));
    }
}

inline bool lt_impl(const bf &a, const bf &b) {
    if (a.is_zero()) {
        return !b.is_zero() && !b.sign();
    }
    if (a.exponent > b.exponent) return false;
    if (a.exponent < b.exponent) return true;
    return a.mantissa < b.mantissa;
}

inline bool lte_impl(const bf &a, const bf &b) {
    if (a.is_zero()) {
        return b.is_zero() || !b.sign();
    }
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

bf bf::truncated() const {
    if (exponent < 0) {
        return 0;
    }
    auto fraction_length = 62 - exponent;
    if (fraction_length < 0) {
        return *this;
    }
    auto mask = (-1L) << fraction_length;
    return bf(exponent, mantissa & mask);
}

bf bf::operator%(const bf &other) const {
    auto div_result = *this / other;
    return *this - (div_result.truncated() * other);
}

std::ostream &bigfloat::operator<<(std::ostream &os, const bf &x) {
    bf remainder = x;
    if (remainder.sign()) {
        remainder = -remainder;
        os << '-';
    }

    // Accumulate tens until we exceed the target
    bf tens_acc = 1;
    std::vector<bf> gt1_powers;
    do {
        gt1_powers.push_back(tens_acc);
        tens_acc *= 10;
    } while (tens_acc < remainder);

    // Divide by powers of 10 until we reach zero
    std::vector<char> digits;
    for (auto it = gt1_powers.rbegin(); it != gt1_powers.rend(); it++) {
        auto p10 = *it;
        if (p10 > remainder) {  // Too big
            os << '0';
            continue;
        }
        auto result = remainder / p10;
        auto trunc = result.truncated();
        auto d = double(trunc);
        auto digit = int(d);
        os << digit;
        remainder -= trunc * p10;
    }

    if (remainder.is_zero()) return os;

    os << '.';
    tens_acc = 1;
    static const bf one_tenth = bf(1) / 10;

    int buffered_zeros = 0;
    for (int i = os.precision(); !remainder.is_zero() && i > 0; i--) {
        tens_acc *= one_tenth;
        if (tens_acc > remainder) {
            buffered_zeros++;
            continue;
        }

        auto result = remainder / tens_acc;
        auto trunc = result.truncated();
        auto d = double(trunc);
        auto digit = int(d);
        remainder -= trunc * tens_acc;

        if (digit == 0) {
            buffered_zeros++;
        } else {
            while (buffered_zeros > 0) {
                os << '0';
                buffered_zeros--;
            }
            os << digit;
        }
    }

    return os;
}
