//
// Created by astrid on 8/18/20.
//

#include "bigfloat.hpp"

bigfloat::bigfloat() : sign(false), mantissa(0), exponent(0) {

}

bigfloat::bigfloat(bool sign, unsigned char exponent, long mantissa) :
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

// Adds a and b, assuming that a's exponent > b's exponent
bigfloat add_impl(const bigfloat a, const bigfloat b) {
    int shift = a.exponent - b.exponent;

    long mta = a.sign ? -a.mantissa : a.mantissa;
    long mtb = b.sign ? -b.mantissa : b.mantissa;

    long shifted_mantissa = mtb << shift;

    bigfloat out;
    out.exponent = a.exponent;
    out.mantissa = mta + shifted_mantissa;

    if (out.mantissa < mta) {  // overflow
        out.mantissa >>= 1;
        out.exponent += 1;
    }

    return out;
}

bigfloat bigfloat::operator+(const bigfloat &other) const {
    if (exponent < other.exponent) {
        return add_impl(other, *this);
    } else {
        return add_impl(*this, other);
    }
}

bigfloat bigfloat::operator-(const bigfloat &other) {
    bigfloat out;
    return out;
}

bigfloat bigfloat::operator*(const bigfloat &other) {
    bigfloat out;
    return out;
}

bigfloat bigfloat::operator/(const bigfloat &other) {
    bigfloat out;
    return out;
}

bool bigfloat::operator==(const bigfloat &other) const {
    return sign == other.sign && mantissa == other.mantissa && exponent == other.exponent;
}

bigfloat::operator float() const {
    ieee754_float f;
    f.mantissa = static_cast<unsigned int>(mantissa >> 40);
    f.exponent = static_cast<short>(exponent);
    f.sign = sign;
    return f.f;
}

bigfloat::operator double() const {
    return 0;
}

bigfloat bigfloat::operator-() const {
    return bigfloat(!sign, mantissa, exponent);
}

void bigfloat::to_mpfr(mpfr_t rop) {
    mpfr_init2(rop, 63);
    mpfr_set_ui_2exp(rop, mantissa, exponent, MPFR_RNDD);
}

bigfloat::bigfloat(std::string x) {

}


std::ostream &operator<<(std::ostream &os, bigfloat x) {
    if (x.sign) {
        os << "-";
    }
    os << "1." << x.mantissa << "e" << (int)x.exponent;
    return os;
}
