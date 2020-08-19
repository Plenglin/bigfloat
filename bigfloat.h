//
// Created by astrid on 8/18/20.
//

#ifndef BIGFLOAT_BIGFLOAT_H
#define BIGFLOAT_BIGFLOAT_H

// Bitmasks for extracting values from raw binary floats

typedef union {
    float f;
    struct {
        unsigned int mantissa : 23;
        unsigned int exponent : 8;
        unsigned int sign : 1;
    };
} ieee754_float;

typedef union {
    double d;
    struct {
        unsigned int mantissa : 52;
        unsigned int exponent : 11;
        unsigned int sign : 1;
    };
} ieee754_double;


// A software-based floating point number object.
// On disk, it is packed into a 80-bit space like so:
// [79:65 exponent] [64 sign] [63:0 mantissa]
struct bigfloat {
    // The mantissa is 63 bits wide. When loaded into memory, the uppermost bit
    // is used to detect overflow.
    unsigned long mantissa;
    short exponent;
    bool sign;

    bigfloat(bool sign, short exponent, unsigned long mantissa);
    explicit bigfloat(double x);
    explicit bigfloat(float x);
};


#endif //BIGFLOAT_BIGFLOAT_H
