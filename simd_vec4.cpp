//
// Created by astrid on 9/7/20.
//

#include <smmintrin.h>
#include "simd_vec4.hpp"

using namespace bigfloat;
using namespace bigfloat::simd;



simd_vec4::simd_vec4(bf x0, bf x1, bf x2, bf x3) {
    mantissa = _mm256_set_epi64x(x3.mantissa, x2.mantissa, x1.mantissa, x0.mantissa);
    exponent = _mm256_set_epi64x(x3.exponent, x2.exponent, x1.exponent, x0.exponent);
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
    return bf(((unsigned long*)&exponent)[i], ((unsigned long*)&mantissa)[i]);
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
