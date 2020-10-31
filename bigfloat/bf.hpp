#pragma clang diagnostic push
#pragma ide diagnostic ignored "google-explicit-constructor"

#ifndef BIGFLOAT_BF_HPP
#define BIGFLOAT_BF_HPP

#include <gmp.h>

#include "ostream"

#define BF_MSB 1L << 62

namespace bigfloat {
    // A packed software-based floating point number object.
    struct bf_packed {
        long mantissa;
        short exponent;
    };

    // A software-based floating point number object.
    struct bf {
        // The mantissa is 62 bits. It has an EXPLICIT 1 for its 63rd bit. Its 64th bit is the sign bit.
        long mantissa;
        short exponent;

        bf();
        bf(short exponent, long mantissa);
        bf(bf_packed x);
        bf(double x);
        bf(int x);
        bf(std::string x, int radix = 10);

        explicit operator double() const;
        explicit operator bf_packed() const;

        inline bf operator+() const {
            return *this;
        }
        inline bf operator-() const {
            return bf(exponent, -mantissa);
        }

        bf operator+(const bf &other) const;
        inline void operator+=(const bf &other) {
            *this = *this + other;
        }

        bf operator-(const bf &other) const;
        inline void operator-=(const bf &other) {
            *this = *this - other;
        }

        bf operator*(const bf &other) const;
        inline void operator*=(const bf &other) {
            *this = *this * other;
        }

        bf fast_div(const bf &other) const;
        bf slow_div(const bf &other) const;
        bf operator/(const bf &other) const;
        inline void operator/=(const bf &other) {
            *this = *this / other;
        }

        bf operator%(const bf &other) const;
        inline void operator%=(const bf &other) {
            *this = *this % other;
        }

        bool operator<(const bf &other) const;
        bool operator>(const bf &other) const;
        bool operator<=(const bf &other) const;
        bool operator>=(const bf &other) const;
        inline bool operator==(const bf &other) const {
            return exponent == other.exponent && mantissa == other.mantissa;
        }
        inline bool operator!=(const bf &other) const {
            return exponent != other.exponent || mantissa != other.mantissa;
        }

        bf truncated() const;

        inline bool sign() const {
            return (unsigned long)mantissa >> 63;
        }
        inline bool is_zero() const {
            return exponent == 0 && mantissa == 0;
        }
        inline bool is_nan() const {
            return (exponent == 32767 || exponent == -32768) && mantissa != 0;
        }
        inline bool is_inf() const {
            return (exponent == 32767 || exponent == -32768) && mantissa == 0;
        }
        inline static bf inf(bool sign) {
            return bf(sign ? 32767 : -32768, 0);
        }
        inline static bf nan(bool sign) {
            return bf(sign ? 32767 : -32768, 1);
        }

        inline static bf max_value() {
            return bf::inf(false);
        }
        inline static bf min_value() {
            return bf::inf(true);
        }

        std::string to_string();
    };
    std::ostream &operator<<(std::ostream &os, const bigfloat::bf &x);
}


#endif //BIGFLOAT_BF_HPP

#pragma clang diagnostic pop