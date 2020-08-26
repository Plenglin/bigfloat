//
// Created by astrid on 8/18/20.
//

#include "bigfloat.hpp"

bigfloat::bigfloat() : sign(false), mantissa(0), exponent(0) {

}

bigfloat::bigfloat(bool sign, unsigned char exponent, unsigned long mantissa) :
        sign(sign),
        mantissa(mantissa),
        exponent(exponent)
{ }

bigfloat::bigfloat(double x) {
    ieee754_double d = {.d = x};
    sign = d.sign;
    mantissa = d.mantissa << 12;
    exponent = (d.exponent - (1023 << 4));
}

bigfloat::bigfloat(float x) {
    ieee754_float f = {.f = x};
    sign = f.sign;
    mantissa = (long)f.mantissa << 40;
    exponent = f.bits >> 23;
}

bigfloat bigfloat::operator+(bigfloat &other) const {
    bigfloat out;
    int smaller_exp, larger_exp;
    if (exponent < other.exponent) {
        larger_exp = other.exponent;
        smaller_exp = exponent;
    } else {
        larger_exp = other.exponent;
        smaller_exp = exponent;
    }



    return out;
}

bigfloat bigfloat::operator-(bigfloat &other) {
    bigfloat out;
    return out;
}

bigfloat bigfloat::operator*(bigfloat &other) {
    bigfloat out;
    return out;
}

bigfloat bigfloat::operator/(bigfloat &other) {
    bigfloat out;
    return out;
}

bool bigfloat::operator==(const bigfloat &other) const {
    return sign == other.sign && mantissa == other.mantissa && exponent == other.exponent;
}

bigfloat::operator float() const {
    ieee754_float f;
    f.mantissa = static_cast<unsigned int>(mantissa >> 40);
    f.exponent = static_cast<short>(exponent >> 7);
    f.sign = sign;
    return f.f;
}

bigfloat::operator double() const {
    return 0;
}

bigfloat bigfloat::operator-() const {
    return bigfloat(!sign, mantissa, exponent);
}

std::ostream &operator<<(std::ostream &os, bigfloat x) {
    if (x.sign) {
        os << "-";
    }
    os << "1." << x.mantissa << "e" << (int)x.exponent;
    return os;
}
