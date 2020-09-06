#pragma clang diagnostic push
#pragma ide diagnostic ignored "google-explicit-constructor"
//
// Created by astrid on 8/18/20.
//

#ifndef BIGFLOAT_BIGFLOAT_HPP
#define BIGFLOAT_BIGFLOAT_HPP

#include <gmp.h>
#include <mpfr.h>

#include "ostream"

// A packed software-based floating point number object.
struct bigfloat_packed {
    unsigned long mantissa : 63;
    bool sign : 1;
    unsigned short exponent;
};

// A software-based floating point number object.
struct bigfloat {
    // The mantissa is 63 bits wide. The uppermost bit is always 1.
    unsigned long mantissa;

    unsigned short exponent;
    bool sign;

    bigfloat();
    bigfloat(bool sign, unsigned short exponent, unsigned long mantissa);
    explicit bigfloat(bigfloat_packed x);
    explicit bigfloat(double x);
    bigfloat(std::string x);

    explicit operator float() const;
    explicit operator double() const;
    explicit operator bigfloat_packed() const;
    void to_mpfr(mpfr_t rop);

    bigfloat operator -() const;

    bigfloat operator +(const bigfloat &other) const;
    bigfloat operator +=(const bigfloat &other);
    bigfloat operator -(const bigfloat &other) const;
    bigfloat operator *(const bigfloat &other) const;
    bigfloat operator /(const bigfloat &other);

    inline bool is_zero() const;

    bool operator ==(const bigfloat &other) const;
};

std::ostream& operator <<(std::ostream &os, bigfloat x);

#endif //BIGFLOAT_BIGFLOAT_HPP

#pragma clang diagnostic pop