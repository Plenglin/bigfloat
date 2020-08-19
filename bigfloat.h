//
// Created by astrid on 8/18/20.
//

#ifndef BIGFLOAT_BIGFLOAT_H
#define BIGFLOAT_BIGFLOAT_H

typedef union {
    float f;
    struct {
        unsigned int mantissa : 23;
        short exponent : 8;
        bool sign : 1;
    };
} ieee754_float;

typedef union {
    double d;
    struct {
        unsigned long mantissa : 52;
        short exponent : 11;
        bool sign : 1;
    };
} ieee754_double;

#define EXPONENT_STEP 0x800

// A software-based floating point number object.
// On disk, it is packed into a 80-bit space like so:
// [79:65 exponent] [64 sign] [63:0 mantissa]
struct bigfloat {
    // The mantissa is 63 bits wide. When loaded into memory, the uppermost bit
    // is used to detect overflow.
    unsigned long mantissa;

    // Though technically 16 bits wide, we only use [14:7]. The highest bit is
    // always zero and the lower 7 are treated as nonexistent.
    unsigned char exponent;
    bool sign;

    bigfloat(bool sign, unsigned char exponent, unsigned long mantissa);
    explicit bigfloat(double x);
    explicit bigfloat(float x);
};


#endif //BIGFLOAT_BIGFLOAT_H
