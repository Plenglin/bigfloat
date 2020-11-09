#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-pro-type-member-init"
#pragma ide diagnostic ignored "portability-simd-intrinsics"
//
// Created by astrid on 9/7/20.
//

#include <smmintrin.h>
#include "simd_vec4.hpp"
#include "avx_helper.hpp"
#include "helpers.inl"

using namespace bigfloat;


simd_vec4::simd_vec4() = default;

simd_vec4::simd_vec4(bf *x) : simd_vec4(x[0], x[1], x[2], x[3]) {

}

simd_vec4::simd_vec4(int sign, __m256i exponent, __m256i mantissa) :
        sign(sign),
        exponent(exponent),
        mantissa(mantissa) {

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

simd_vec4::simd_vec4(__m256d ds) {
    helper::m256_union du;
    du.v = (__m256i)ds;
    sign = ((du.q[3] >> 63) << 3) |
            ((du.q[2] >> 63) << 2) |
            ((du.q[1] >> 63) << 1) |
            (du.q[0] >> 63);

    auto mt = (__m256i)ds;
    mt = _mm256_slli_epi64(mt, 12);  // cut off exp
    mt = _mm256_srli_epi64(mt, 2);
    mt = _mm256_or_si256(mt, _mm256_set1_epi64x(BF_MSB));

    auto ex = (__m256i)ds;
    ex = _mm256_slli_epi64(ex, 1);  // cut off sign
    ex = _mm256_srli_epi64(ex, 53);
    ex = _mm256_sub_epi64(ex, _mm256_set1_epi64x(IEEE_754_EXP_BIAS));

    mantissa = mt;
    exponent = ex;
}

simd_vec4::operator __m256d() const {
    helper::m256_union s;
    for (int i = 0; i < 4; i++) {
        s.q[i] = ((sign >> i) & 1) ? (1UL << 63) : 0;
    }

    __m256i mt = _mm256_slli_epi64(mantissa, 2);  // cut off 1
    mt = _mm256_srli_epi64(mt, 12);

    __m256i ex = _mm256_add_epi64(exponent, _mm256_set1_epi64x(IEEE_754_EXP_BIAS));
    ex = _mm256_slli_epi64(ex, 53);  // cut off upper bits
    ex = _mm256_srli_epi64(ex, 1);

    return (__m256d)_mm256_or_si256(_mm256_or_si256(s.v, mt), ex);
}

inline __m256i has_high_bit(__m256i x) {
    x = _mm256_srai_epi32(x, 32);
    return (__m256i)_mm256_movehdup_ps((__m256)x);
}

// Swaps a and b, if their corresponding mask term is 1.
inline void masked_swap(__m256i &a, __m256i &b, __m256i mask) {
    __m256i ta = _mm256_blendv_epi8(a, b, mask);
    __m256i tb = _mm256_blendv_epi8(b, a, mask);
    a = ta;
    b = tb;
}

// Sorts and aligns exponents.
inline void sort_align_exponent(__m256i &sa, __m256i &exa, __m256i &mta, __m256i &sb, __m256i exb, __m256i &mtb, __m256i zeros) {
    // Subtract exponents to compare
    __m256i sediff = _mm256_sub_epi64(exa, exb);

    {
        // Swap values to have greater on left
        __m256i swap_mask = _mm256_cmpgt_epi64(zeros, sediff);
        masked_swap(mta, mtb, swap_mask);
        masked_swap(exa, exb, swap_mask);
        masked_swap(sa, sb, swap_mask);
    }

    // Shift smaller mantissa and add to exponent
    __m256i neg_exb = has_high_bit(sediff);

    // abs(shift) via 2's complement
    __m256i shift = _mm256_add_epi64(sediff, neg_exb);
    shift = _mm256_xor_si256(shift, neg_exb);
    mtb = _mm256_srlv_epi64(mtb, shift);
}

inline __m256i addition(__m256i exa, __m256i mta, __m256i mtb, __m256i &exo, __m256i &mto) {
    // Perform the operation
    __m256i sum = _mm256_add_epi64(mta, mtb);

    // Overflow handling: shift right 1, with correct sign
    __m256i overflow = has_high_bit(sum);
    __m256i ones = _mm256_set1_epi64x(1);

    __m256i mt_srl1 = _mm256_srlv_epi64(sum, ones);

    mto = _mm256_blendv_epi8(sum, mt_srl1, overflow);
    exo = _mm256_sub_epi64(exa, overflow);
}

inline __m256i subtraction(__m256i sa, __m256i exa, __m256i mta, __m256i mtb, __m256i &so, __m256i &exo, __m256i &mto) {
    helper::m256_union abs, lz;

    // Perform the operation
    __m256i diff = _mm256_sub_epi64(mta, mtb);

    // Sign adjustment
    __m256i sc = has_high_bit(diff);
    so = _mm256_xor_si256(sa, sc);

    // Absolute value
    abs.v = _mm256_add_epi64(diff, sc);
    abs.v = _mm256_xor_si256(abs.v, sc);

    // Count number of leading zeros
    for (int i = 0; i < 4; i++) {
        lz.q[i] = __builtin_clzl(abs.q[i]);
    }

    // Shift left by lz - 1.
    __m256i shift_count = _mm256_sub_epi64(lz.v, _mm256_set1_epi64x(1));
    __m256i result_sll_lz = _mm256_sllv_epi64(abs.v, shift_count);

    // Exponent adjustment
    exo = _mm256_sub_epi64(exa, shift_count);
    mto = result_sll_lz;

    // Zero checking
    __m256i is_zero = _mm256_cmpeq_epi64(_mm256_setzero_si256(), mto);
    exo = _mm256_andnot_si256(is_zero, exo);
}

simd_vec4 simd_vec4::operator+(simd_vec4 &other) const {
    __m256i zeros = _mm256_setzero_si256();
    helper::m256_union sau, sbu;
    for (int i = 0; i < 4; i++) {
        sau.q[i] = ((sign >> i) & 1) ? -1 : 0;
        sbu.q[i] = ((other.sign >> i) & 1) ? -1 : 0;
    }

    __m256i exa = exponent;
    __m256i mta = mantissa;
    __m256i exb = other.exponent;
    __m256i mtb = other.mantissa;
    __m256i sa = sau.v;
    __m256i sb = sbu.v;

    sort_align_exponent(sa, exa, mta, sb, exb, mtb, zeros);

    __m256i add_so, add_exo, add_mto, sub_so, sub_exo, sub_mto;
    __m256i op = _mm256_xor_si256(sa, sb);
    add_so = sa;
    addition(exa, mta, mtb, add_exo, add_mto);
    subtraction(sa, exa, mta, mtb, sub_so, sub_exo, sub_mto);

    helper::m256_union sou;
    sou.v = _mm256_blendv_epi8(add_so, sub_so, op);

    return simd_vec4(
            ((sou.q[3] >> 63) << 3) | ((sou.q[2] >> 63) << 2) | ((sou.q[1] >> 63) << 1) | (sou.q[0] >> 63),
            _mm256_blendv_epi8(add_exo, sub_exo, op),
            _mm256_blendv_epi8(add_mto, sub_mto, op));
}

void simd_vec4::operator+=(simd_vec4 &other) {
    *this = *this + other;
}

simd_vec4 simd_vec4::operator-(simd_vec4 &other) const {
    auto n = -other;
    return *this + n;
}

void simd_vec4::operator-=(simd_vec4 &other) {
    other.negate();
    *this += other;
    other.negate();
}

simd_vec4 simd_vec4::operator*(simd_vec4 &other) const {
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
    __m256i has_upper_bit_mask = has_high_bit(mulv);

    // Shift upper bit mantissas right by 1
    __m256i mulv_all_srl1 = _mm256_srli_epi64(mulv, 1);
    __m256i mto = _mm256_blendv_epi8(mulv, mulv_all_srl1, has_upper_bit_mask);

    // Add exponents
    __m256i exp_sum = _mm256_add_epi64(exponent, other.exponent);

    // Decrement upper bit exponents by 1
    __m256i exo = _mm256_sub_epi64(exp_sum, has_upper_bit_mask);

    return simd_vec4(sign ^ other.sign, exo, mto);
}

void simd_vec4::operator*=(simd_vec4 &other) {
    *this = *this * other;
}

bf_ref simd_vec4::operator[](int i) const {
    return {
        .parent = (simd_vec4*)this,
        .i = i
    };
}

void simd_vec4::invert() {

}

simd_vec4 simd_vec4::operator/(simd_vec4 &other) const {
    auto inv = _mm256_div_pd(_mm256_set1_pd(1), __m256d(other));
    auto other_inv = simd_vec4(inv);
    return *this * other_inv;
}

void simd_vec4::operator/=(simd_vec4 &other) {
    *this = *this / other;
}

void simd_vec4::negate() {
    sign = ~sign;
}

simd_vec4 simd_vec4::operator-() const {
    return simd_vec4(~sign, exponent, mantissa);
}

bool simd_vec4::operator==(simd_vec4 &other) {
    auto exponent_neq = _mm256_xor_si256(exponent, other.exponent);
    auto mantissa_neq = _mm256_xor_si256(exponent, other.exponent);

    bool exp_mant_eq = _mm256_testz_si256(exponent_neq, mantissa_neq);
    return (((sign ^ other.sign) & 0xf) == 0) && exp_mant_eq;
}

bool simd_vec4::operator!=(simd_vec4 &other) {
    return !(*this == other);
}

simd_vec4 simd_vec4::operator+(bf other) const {
    auto v_other = simd_vec4(other);
    return *this + v_other;
}

simd_vec4 simd_vec4::operator-(bf other) const {
    auto v_other = simd_vec4(other);
    return *this - v_other;
}

simd_vec4 simd_vec4::operator*(bf other) const {
    auto v_other = simd_vec4(other);
    return *this * v_other;
}

simd_vec4 simd_vec4::operator/(bf other) const {
    auto v_other = simd_vec4(other);
    return *this / v_other;
}

simd_vec4 simd_vec4::operator+(bf_ref other) const {
    return *this + bf(other);
}

simd_vec4 simd_vec4::operator-(bf_ref other) const {
    return *this - bf(other);
}

simd_vec4 simd_vec4::operator*(bf_ref other) const {
    return *this * bf(other);
}

simd_vec4 simd_vec4::operator/(bf_ref other) const {
    return *this / bf(other);
}

bf bigfloat::dot(simd_vec4 &a, simd_vec4 &b) {
    auto prods = a * b;
    auto acc = bf(0);
    for (int i = 0; i < 4; i++) {
        acc += prods[i];
    }
    return acc;
}

#pragma clang diagnostic pop