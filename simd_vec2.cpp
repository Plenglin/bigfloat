//
// Created by astrid on 9/7/20.
//

#include <smmintrin.h>
#include "simd_vec2.hpp"

using namespace bigfloat;


simd::vec2::vec2(bf x0, bf x1) {
    mantissa = _mm_set_epi64x(x1.mantissa, x0.mantissa);
    exponent = _mm_set_epi64x(x1.exponent, x0.exponent);
    sign = (x1.sign << 1) | x0.sign;
}

void simd::vec2::operator+=(simd::vec2 &other) {

}

void simd::vec2::operator*=(simd::vec2 &other) {
    int sa = sign;
    int sb = other.sign;
    __m128i exa = exponent;
    __m128i exb = other.exponent;
    __m128i mta = mantissa;
    __m128i mtb = other.mantissa;

    // Swap a and b if b > a
    __m128i exa_gt_exb = _mm_cmpgt_epi64(exa, exb);
}

bf simd::vec2::operator[](int i) {
    return bf((sign >> i) & 1, ((unsigned long*)&exponent)[i], ((unsigned long*)&mantissa)[i]);
}