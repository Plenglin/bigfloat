#pragma clang diagnostic push
#pragma ide diagnostic ignored "google-explicit-constructor"

#ifndef BIGFLOAT_BIGFLOAT_HPP
#define BIGFLOAT_BIGFLOAT_HPP

#include <gmp.h>

#include "ostream"

namespace bigfloat {
    // A packed software-based floating point number object.
    struct bf_packed {
        unsigned long mantissa: 63;
        bool sign: 1;
        unsigned short exponent;
    };

    // A software-based floating point number object.
    struct bf {
        // The mantissa is 63 bits wide. The uppermost bit is always 1.
        unsigned long mantissa;

        unsigned short exponent;
        bool sign;

        bf();

        bf(bool sign, unsigned short exponent, unsigned long mantissa);

        explicit bf(bf_packed x);

        explicit bf(double x);

        bf(std::string x);

        explicit operator double() const;

        explicit operator bf_packed() const;

        short unbiased_exponent() const;

        inline bf operator-() const;

        inline bf operator+() const;

        bf operator+(const bf &other) const;

        bf operator+=(const bf &other);

        bf operator-(const bf &other) const;

        bf operator*(const bf &other) const;

        bf operator/(const bf &other) const;

        bool operator<(const bf &other) const;

        bool operator>(const bf &other) const;

        bool operator<=(const bf &other) const;

        bool operator>=(const bf &other) const;

        bool operator==(const bf &other) const;

        inline bool is_zero() const;

        inline bool is_nan() const;

        inline static bf inf(bool sign);

        inline static bf nan(bool sign);
    };
}

std::ostream &operator<<(std::ostream &os, bigfloat::bf x);

#endif //BIGFLOAT_BIGFLOAT_HPP

#pragma clang diagnostic pop