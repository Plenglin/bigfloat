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

typedef union {
    float f;
    unsigned int bits;
    struct {
        unsigned int mantissa : 23;
        short exponent : 8;
        bool sign : 1;
    };
} ieee754_float;

typedef union {
    double d;
    unsigned long bits;
    struct {
        unsigned long mantissa : 52;
        short exponent : 11;
        bool sign : 1;
    };
} ieee754_double;

#define EXPONENT_STEP 0x800

// A software-based floating point number object.
struct bigfloat {
    // The mantissa is 63 bits wide. The uppermost bit is always 1.
    unsigned long mantissa;

    unsigned char exponent;
    bool sign;

    bigfloat();
    bigfloat(bool sign, unsigned char exponent, unsigned long mantissa);
    bigfloat(double x);
    bigfloat(float x);
    bigfloat(std::string x);

    operator float() const;
    operator double() const;
    void to_mpfr(mpfr_t rop);

    bigfloat operator -() const;

    bigfloat operator +(const bigfloat &other) const;
    bigfloat operator -(const bigfloat &other);
    bigfloat operator *(const bigfloat &other);
    bigfloat operator /(const bigfloat &other);

    bool operator ==(const bigfloat &other) const;
};

std::ostream& operator <<(std::ostream &os, bigfloat x);

#endif //BIGFLOAT_BIGFLOAT_HPP

#pragma clang diagnostic pop