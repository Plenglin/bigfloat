//
// Created by astrid on 9/7/20.
//

#include <smmintrin.h>
#include "simd_vec4.hpp"

using namespace bigfloat;
using namespace bigfloat::simd;

#define CONDITIONAL_INV(s, m) s ? -m : m

simd_vec4::simd_vec4(const bf &x0, const bf &x1, const bf &x2, const bf &x3) {
    bool s0 = x0.sign();
    bool s1 = x1.sign();
    bool s2 = x2.sign();
    bool s3 = x3.sign();
    sign = (s3 << 3) | (s2 << 2) | (s1 << 1) | s0;
    mantissa = _mm256_set_epi64x(
            CONDITIONAL_INV(s3, x3.mantissa),
            CONDITIONAL_INV(s2, x2.mantissa),
            CONDITIONAL_INV(s1, x1.mantissa),
            CONDITIONAL_INV(s0, x0.mantissa));
    exponent = _mm_set_epi32(x3.exponent, x2.exponent, x1.exponent, x0.exponent);
}

simd_vec4::simd_vec4(bf x) : simd_vec4(x, x, x, x) {

}

void simd_vec4::operator+=(simd_vec4 &other) {

}

void simd_vec4::operator*=(simd_vec4 &other) {
    sign ^= other.sign;

    //
}

bf simd_vec4::operator[](int i) const {
    return bf(
            ((int*)&exponent)[i],
            CONDITIONAL_INV((sign >> i) & 1, ((long*)&mantissa)[i]));
}

void simd_vec4::invert() {

}

void simd_vec4::operator/=(simd_vec4 &other) {

}

void simd_vec4::negate() {

}

std::ostream &operator<<(std::ostream &os, const simd_vec4 &x) {
    os << "simd_vec4[" << x[0] << "," << x[1] << "," << x[2] << "," << x[3] << "]";
    return os;
}
