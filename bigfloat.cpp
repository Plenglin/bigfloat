//
// Created by astrid on 8/18/20.
//

#include "bigfloat.h"

bigfloat::bigfloat(bool sign, unsigned char exponent, unsigned long mantissa) :
        sign(sign),
        mantissa(mantissa),
        exponent(exponent)
{ }

bigfloat::bigfloat(double x) {
    ieee754_double d = {.d = x};
    sign = d.sign;
    mantissa = d.mantissa;
    exponent = d.exponent;
}

bigfloat::bigfloat(float x) {
    ieee754_float f = {.f = x};
    sign = f.sign;
    mantissa = (long)f.mantissa << 40;
    exponent = (*(unsigned int*)&x) >> 23;
}
