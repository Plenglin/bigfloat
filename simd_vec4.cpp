//
// Created by astrid on 9/7/20.
//

#include <smmintrin.h>
#include "simd_vec4.hpp"
#include "avx_helper.hpp"

using namespace bigfloat;
using namespace bigfloat::simd;

#define CONDITIONAL_INV(s, m) s ? -m : m


simd_vec4::simd_vec4(__m256i exponent, __m256i mantissa) : exponent(exponent), mantissa(mantissa) {

}

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
    exponent = _mm256_set_epi64x(x3.exponent, x2.exponent, x1.exponent, x0.exponent);
}

simd_vec4::simd_vec4(bf x) : simd_vec4(x, x, x, x) {

}

void simd_vec4::operator+=(simd_vec4 &other) {
}


void simd_vec4::operator*=(simd_vec4 &other) {
    // Handle signs
    sign ^= other.sign;

    // Multiply mantissas
    helper::m256_union muls;
    for (int i = 0; i < 4; i++) {
        unsigned __int128 mul =
                (unsigned __int128)(mantissa_array[i]) *
                (unsigned __int128)(other.mantissa_array[i]);
        unsigned long upper = mul >> 62;
        muls.q[i] = upper;
    }

    // Build vector
    __m256i mulv = muls.v;

    // Build a mask for items with 1 in bit 63
    __m256i zeros = _mm256_setzero_si256();
    __m256i has_upper_bit_mask = _mm256_cmpgt_epi64(zeros, mulv);

    // Shift upper bit mantissas right by 1
    __m256i mulv_all_srl1 = _mm256_srli_epi64(mulv, 1);
    __m256i mto = _mm256_blendv_epi8(mulv, mulv_all_srl1, has_upper_bit_mask);

    // Add exponents
    __m256i exp_sum = _mm256_add_epi64(exponent, other.exponent);

    // Decrement upper bit exponents by 1
    __m256i exo = _mm256_sub_epi64(exp_sum, has_upper_bit_mask);

    mantissa = mto;
    exponent = exo;
}

bf simd_vec4::operator[](int i) const {
    return bf(
            exponent_array[i],
            CONDITIONAL_INV((sign >> i) & 1, (mantissa_array[i]))
    );
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
