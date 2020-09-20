#pragma clang diagnostic push
#pragma ide diagnostic ignored "portability-simd-intrinsics"
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
    __m256i zeros = _mm256_setzero_si256();
    helper::m256_union sa, sb;
    for (int i = 0; i < 4; i++) {
        sa.q[i] = ((sign >> i) & 1) ? -1 : 0;
        sb.q[i] = ((other.sign >> i) & 1) ? -1 : 0;
    }

    // Perform addition or subtraction. Note that both operations are
    // guaranteed to not overflow because the MSB is always at bit 62.
    __m256i mta = mantissa;
    __m256i mtb = other.mantissa;
    __m256i add_result = _mm256_add_epi64(mta, mtb);
    __m256i sub_result = _mm256_sub_epi64(mta, mtb);

    // Select the results from the correct operation.
    __m256i operation = _mm256_xor_si256(sa.v, sb.v);
    __m256i result = _mm256_blendv_epi8(add_result, sub_result, operation);

    // Upper bit/sign change
    __m256i ubsc = _mm256_cmpgt_epi64(zeros, result);

    // FOR ADDITION: if upper bit then srl 1 (overflow handling)
    __m256i result_srl1 = _mm256_srli_epi64(result, 1);
    add_result = _mm256_blendv_epi8(add_result, result_srl1, ubsc);

    // FOR SUBTRACTION: if sign change then negate (for absolute value)
    helper::m256_union sub_negate;
    sub_negate.v = helper::conditional_negate(ubsc, result);

    __m256i neg_sc = (sa.v, ubsc);

    // Count number of leading zeros
    helper::m256_union lz;
    for (int i = 0; i < 4; i++) {
        lz.q[i] = __builtin_clzl(result.q[i]);
    }

    // Shift right by 1, or shift left by lz - 1.
    __m256i shift_count = _mm256_sub_epi64(lz.v, _mm256_set1_epi64x(1));
    __m256i result_sll_lz = _mm256_sllv_epi64(result.v, shift_count);

    // Select the correct operation.
    __m256i has_upper_bit = ubsc;
    __m256i mto = _mm256_blendv_epi8(result_srl1, result_sll_lz, has_upper_bit);

    // Adjust exponent.
    __m256i exo = _mm256_sub_epi64(exponent, shift_count);

    mantissa = mto;
    exponent = exo;
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

#pragma clang diagnostic pop