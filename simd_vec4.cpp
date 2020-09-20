//
// Created by astrid on 9/7/20.
//

#include <smmintrin.h>
#include "simd_vec4.hpp"

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
            CONDITIONAL_INV(s3, x3.mantissa << 1),
            CONDITIONAL_INV(s2, x2.mantissa << 1),
            CONDITIONAL_INV(s1, x1.mantissa << 1),
            CONDITIONAL_INV(s0, x0.mantissa << 1));
    exponent = _mm256_set_epi64x(x3.exponent, x2.exponent, x1.exponent, x0.exponent);
}

simd_vec4::simd_vec4(bf x) : simd_vec4(x, x, x, x) {

}

void simd_vec4::operator+=(simd_vec4 &other) {

}


void simd_vec4::operator*=(simd_vec4 &other) {
    // Force the data to be aligned to a 4-byte boundary.
    long _padding;
    // Handle signs
    sign ^= other.sign;

    // Multiply mantissas
    unsigned long muls[4];
    for (int i = 0; i < 4; i++) {
        unsigned __int128 mul = (unsigned __int128)mantissa_array[i] * (unsigned __int128)other.mantissa_array[i];
        unsigned long upper = mul >> 64;
        muls[i] = upper;
    }

    // Build vector
    __m256i mulv = _mm256_loadu_si256((__m256i*)muls);

    // Bootleg 64-bit sra 63 (spread bit 63 across all bits) to build a mask
    __m256i has_upper_bit_mask = _mm256_srai_epi32(mulv, 31);
    has_upper_bit_mask = (__m256i)_mm256_permute_ps((__m256)has_upper_bit_mask, 0b11011101);

    // Shift unmasked mantissas left by 1
    __m256i mulv_all_sll1 = _mm256_slli_epi64(mulv, 1);
    mantissa = _mm256_blendv_epi8(mulv_all_sll1, mulv, has_upper_bit_mask);

    // Add exponents
    __m256i exp_sum = _mm256_add_epi64(exponent, other.exponent);

    // Decrement unmasked exponents by 1. Note that performing a bitwise NOT on the
    // mask creates -1's where the zeros used to be.
    //__m256i all1s = _mm256_set1_epi32(-1);
    //__m256i addend = _mm256_xor_si256(has_upper_bit_mask, all1s);
    //exponent = _mm256_add_epi64(exp_sum, addend);
    exponent = exp_sum;
}

bf simd_vec4::operator[](int i) const {
    return bf(
            exponent_array[i],
            CONDITIONAL_INV((sign >> i) & 1, (mantissa_array[i] >> 1))
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
