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

bf::bf() : sign(false), mantissa(0), exponent(0) {

}

bf::bf(bool sign, unsigned short exponent, unsigned long mantissa) :
        sign(sign),
        mantissa(mantissa),
        exponent(exponent)
{ }

bf::bf(double x) {
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

bf::bf(std::string x) {

}

bf::bf(bf_packed x) {
    sign = x.sign;
    mantissa = x.mantissa;
    exponent = x.exponent;
}

bf::operator bf_packed() const {
    return bf_packed{
        .mantissa = mantissa,
        .sign = sign,
        .exponent = exponent,
    };
}

bf::operator double() const {
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
inline bf add_impl(bool sa, int exa, unsigned long mta, int exb, unsigned long mtb) {
    // Shift to align decimal points
    mtb >>= exa - exb;

    // Invert if subtracting
    if (!adding) {
        mtb = -mtb;
    }

    // Perform addition
    unsigned long mto = mta + mtb;

    if (!adding) {
        int leading_zeros = __builtin_clzl(mto);
        mto <<= leading_zeros;
        unsigned short exo = exa;
        exo -= leading_zeros;
        return bf(sa, exo, mto);
    }

    // Overflow handling
    bool flag = mto < mta;

    unsigned short exo = exa + flag;
    mto >>= flag;
    mto |= ((unsigned long)flag << 63);
    return bf(sa, exo, mto);
}

#define FLAG_A_GTE_B 2
#define FLAG_DIFF_SIGNS 1

#pragma clang diagnostic push
#pragma ide diagnostic ignored "hicpp-multiway-paths-covered"
template <bool calling_addition>
inline bf norm_sort_signs_impl(bool sa, int exa, unsigned long mta, bool sb, int exb, unsigned long mtb) {
    const int flags = (sa != sb) | ((exa >= exb) << 1);

    // Doing it with a switch statement shaves off a Very Good (tm) amount of time.
    // Take your 2 values, a and b. Apply the following operations to them in this order:
    // 1. If we're not calling addition, we are performing subtraction, so invert the sign of b.
    // 2. If a < b, swap their values. (The greater one must be on the left side.)
    // 3. If a's sign != b's sign, then we're performing true subtraction. Otherwise, we're performing true addition.
    if (calling_addition) {
        switch (flags) {
            case FLAG_A_GTE_B | FLAG_DIFF_SIGNS:
                return add_impl<false>(sa, exa, mta, exb, mtb);
            case FLAG_A_GTE_B:
                return add_impl<true>(sa, exa, mta, exb, mtb);
            case FLAG_DIFF_SIGNS:
                return add_impl<false>(sb, exb, mtb, exa, mta);
            case 0:
                return add_impl<true>(sb, exb, mtb, exa, mta);
        }
    } else {
        switch (flags) {
            case FLAG_A_GTE_B | FLAG_DIFF_SIGNS:
                return add_impl<true>(sa, exa, mta, exb, mtb);
            case FLAG_A_GTE_B:
                return add_impl<false>(sa, exa, mta, exb, mtb);
            case FLAG_DIFF_SIGNS:
                return add_impl<true>(!sb, exb, mtb, exa, mta);
            case 0:
                return add_impl<false>(!sb, exb, mtb, exa, mta);
        }
    }
    throw std::exception();
}
#pragma clang diagnostic pop

template <bool calling_addition>
inline bf add_impl_deconstruct(const bf &a, const bf &b) {
    return norm_sort_signs_impl<calling_addition>(
            a.sign,
            a.exponent,
            a.mantissa,
            b.sign,
            b.exponent,
            b.mantissa
    );
}

bf bf::operator+(const bf &other) const {
    return add_impl_deconstruct<true>(*this, other);
}

void bf::operator+=(const bf &other) {
    *this = *this + other;
}

void bf::operator*=(const bf &other) {
    *this = *this + other;
}

bf bf::operator-(const bf &other) const {
    return add_impl_deconstruct<false>(*this, other);
}

inline bf mult_impl(bool sa, int exa, unsigned long mta, bool sb, int exb, unsigned long mtb) {
    // Multiply mantissas
    unsigned __int128 mul = (unsigned __int128)mta * (unsigned __int128)mtb;

    // Extract leading zeros
    unsigned long result_upper = mul >> 64;
    int leading_zeros = __builtin_clzl(result_upper);

    // Normalize exponent and mantissa
    unsigned long mto = mul >> (64 - leading_zeros);
    int exo = exa + exb - leading_zeros - 1022;  // Bias - 1

    return bf(sa ^ sb, exo, mto);
}

bf bf::operator*(const bf &other) const {
    if (is_zero() || other.is_zero()) {
        return bf(sign ^ other.sign, 0, 0);
    }
    return mult_impl(sign, exponent, mantissa, other.sign, other.exponent, other.mantissa);
}

inline bf div_impl(bool sign, int exa, unsigned long mta, int exb, unsigned long mtb) {
    // Divide mantissas
    unsigned __int128 result = ((unsigned __int128)mta << 64) / (unsigned __int128)mtb;

    // Extract leading zeros
    unsigned long result_upper = result >> 64;
    if (result_upper) {
        // There is upper stuff
        int leading_zeros = __builtin_clzl(result_upper);
        unsigned long mto = result >> (64 - leading_zeros);

        // Subtract and normalize exponents
        const auto exo = exa - exb + leading_zeros + (1024 - 64);  // bias + 1 - 64
        return bf(sign, exo, mto);
    } else {
        // There is no upper stuff
        int leading_zeros = __builtin_clzl((unsigned long) result);
        unsigned long mto = result << leading_zeros;

        // Subtract and normalize exponents
        const auto exo = exa - exb + -leading_zeros + 1022;  // bias + 1 - 64
        return bf(sign, exo, mto);
    }
}

bf bf::operator/(const bf &other) const {
    int zero = (is_zero() << 1) | other.is_zero();
    switch (zero) {
        case 0b00:  // x / y
            return div_impl(sign ^ other.sign, exponent, mantissa, other.exponent, other.mantissa);
        case 0b10:  // 0 / y
            return bf(sign ^ other.sign, 0, 0);  // signed zero
        case 0b01:  // x / 0
            return bf::inf(sign ^ other.sign);
        case 0b11:  // 0 / 0
            return bf::nan(!sign ^ other.sign);
    }
    return bf();
}

bool bf::operator==(const bf &other) const {
    return sign == other.sign && mantissa == other.mantissa && exponent == other.exponent;
}

bf bf::operator-() const {
    return bf(!sign, mantissa, exponent);
}

bf bf::operator+() const {
    return *this;
}

bool bf::is_zero() const {
    return !(mantissa || exponent);
}

bool bf::is_nan() const {
    return exponent == (unsigned short)-1 && mantissa;
}

bf bf::inf(bool sign) {
    return bf(sign, -1, 0);
}

bf bf::nan(bool sign) {
    return bf(sign, -1, 1);
}

short bf::unbiased_exponent() const {
    return (short)(exponent - 1023);
}

inline bool le_impl(const bf &a, const bf &b) {
    return a.exponent < b.exponent || a.mantissa < b.mantissa;
}

inline bool leq_impl(const bf &a, const bf &b) {
    return a.exponent <= b.exponent || a.mantissa <= b.mantissa;
}

template<bool (*cmp)(const bf&, const bf&), bool mp_result>
inline bool cmp_impl(const bf &a, const bf &b) {
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

bool bf::operator<(const bf &other) const {
    return cmp_impl<le_impl, true>(*this, other);
}

bool bf::operator>(const bf &other) const {
    return cmp_impl<leq_impl, true>(*this, other);
}

std::ostream &operator<<(std::ostream &os, bf x) {
    std::vector<char> digits;
    auto ten = bf(1);
    while (x > ten) {

    }
    auto remainder = x;

    if (x.sign) {
        os << "-";
    }
    return os;
}
