//
// Created by astrid on 9/7/20.
//

#include <smmintrin.h>
#include "simd_vec4.hpp"

using namespace bigfloat;


simd::vec4::vec4(bf x0, bf x1, bf x2, bf x3) {
    mantissa = _mm256_set_epi64x(x3.mantissa, x2.mantissa, x1.mantissa, x0.mantissa);
    exponent = _mm256_set_epi64x(x3.exponent, x2.exponent, x1.exponent, x0.exponent);
}

void simd::vec4::operator+=(simd::vec4 &other) {

}

void simd::vec4::operator*=(simd::vec4 &other) {
    sign ^= other.sign;

    //
}

bf simd::vec4::operator[](int i) {
    return bf(((unsigned long*)&exponent)[i], ((unsigned long*)&mantissa)[i]);
}
