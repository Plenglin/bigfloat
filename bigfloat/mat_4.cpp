//
// Created by astrid on 10/8/20.
//

#include "mat_4.hpp"
#include "simd.hpp"
#include "helpers.inl"
#include <immintrin.h>

using namespace bigfloat;
using namespace bigfloat::simd;

mat4::mat4() {

}

mat4::mat4(bf m0, bf m1, bf m2, bf m3, bf m4, bf m5, bf m6, bf m7, bf m8, bf m9, bf m10, bf m11, bf m12, bf m13, bf m14,
           bf m15) {
    int sign;
    int signs;

    exponents[15] = m15.exponent;
    sign = m15.sign();
    mantissas[15] = CONDITIONAL_INV(sign, m15.mantissa);
    signs = (signs << 1) | sign;

    exponents[14] = m14.exponent;
    sign = m14.sign();
    mantissas[14] = CONDITIONAL_INV(sign, m14.mantissa);
    signs = (signs << 1) | sign;

    exponents[13] = m13.exponent;
    sign = m13.sign();
    mantissas[13] = CONDITIONAL_INV(sign, m13.mantissa);
    signs = (signs << 1) | sign;

    exponents[12] = m12.exponent;
    sign = m12.sign();
    mantissas[12] = CONDITIONAL_INV(sign, m12.mantissa);
    signs = (signs << 1) | sign;

    exponents[11] = m11.exponent;
    sign = m11.sign();
    mantissas[11] = CONDITIONAL_INV(sign, m11.mantissa);
    signs = (signs << 1) | sign;

    exponents[10] = m10.exponent;
    sign = m10.sign();
    mantissas[10] = CONDITIONAL_INV(sign, m10.mantissa);
    signs = (signs << 1) | sign;

    exponents[9] = m9.exponent;
    sign = m9.sign();
    mantissas[9] = CONDITIONAL_INV(sign, m9.mantissa);
    signs = (signs << 1) | sign;

    exponents[8] = m8.exponent;
    sign = m8.sign();
    mantissas[8] = CONDITIONAL_INV(sign, m8.mantissa);
    signs = (signs << 1) | sign;

    exponents[7] = m7.exponent;
    sign = m7.sign();
    mantissas[7] = CONDITIONAL_INV(sign, m7.mantissa);
    signs = (signs << 1) | sign;

    exponents[6] = m6.exponent;
    sign = m6.sign();
    mantissas[6] = CONDITIONAL_INV(sign, m6.mantissa);
    signs = (signs << 1) | sign;

    exponents[5] = m5.exponent;
    sign = m5.sign();
    mantissas[5] = CONDITIONAL_INV(sign, m5.mantissa);
    signs = (signs << 1) | sign;

    exponents[4] = m4.exponent;
    sign = m4.sign();
    mantissas[4] = CONDITIONAL_INV(sign, m4.mantissa);
    signs = (signs << 1) | sign;

    exponents[3] = m3.exponent;
    sign = m3.sign();
    mantissas[3] = CONDITIONAL_INV(sign, m3.mantissa);
    signs = (signs << 1) | sign;

    exponents[2] = m2.exponent;
    sign = m2.sign();
    mantissas[2] = CONDITIONAL_INV(sign, m2.mantissa);
    signs = (signs << 1) | sign;

    exponents[1] = m1.exponent;
    sign = m1.sign();
    mantissas[1] = CONDITIONAL_INV(sign, m1.mantissa);
    signs = (signs << 1) | sign;

    exponents[0] = m0.exponent;
    sign = m0.sign();
    mantissas[0] = CONDITIONAL_INV(sign, m0.mantissa);
    signs = (signs << 1) | sign;

    this->signs = signs;
}


mat4::mat4(bf a, bf b, bf c, bf d) :    mat4(
        a, 0, 0, 0,
        0, b, 0, 0,
        0, 0, c, 0,
        0, 0, 0, d)
{ }

mat4::mat4(bf x) : mat4(x, x, x, x)
{ }


void mat4::transpose() {

}

void mat4::invert() {

}

void mat4::mul_componentwise(mat4 &other) {

}

void mat4::operator+=(mat4 &other) {

}

void mat4::operator-=(mat4 &other) {

}

mat4 mat4::operator+(mat4 &other) {
    return mat4();
}

mat4 mat4::operator-(mat4 &other) {
    return mat4();
}

mat4 mat4::operator*(mat4 &other) {
    mat4 out;

    __m256i ones = _mm256_set1_epi64x(1);
    __m256i row_indices = _mm256_set_epi64x(0, 4, 8, 12);
    __m256i row_sign_shift = _mm256_set_epi64x(0, 4, 8, 12);
    for (int i = 0; i < 4; i++) {
        auto row_mants = _mm256_i64gather_epi64(mantissas, row_indices, 8);
        auto row_exps = _mm256_set_epi64x(exponents[i + 9], exponents[i + 6], exponents[i + 3], exponents[i]);
        int row_signs = (signs >> i) & 1;
        row_signs |= (signs >> (i + 3)) & 2;
        row_signs |= (signs >> (i + 6)) & 4;
        row_signs |= (signs >> (i + 9)) & 8;

        row_indices = _mm256_add_epi64(row_indices, ones);
        vec4 row(row_signs, row_exps, row_mants);
        vec4 acc(0);

        for (int j = 0; j < 4; j++) {
            int col_offset = j * 4;
            auto col_mants = _mm256_load_si256(v_mantissas + j);
            union {
                unsigned long v_exps;
                short exps[4];
            };
            v_exps = exponents[j];

            auto col_exps = _mm256_set_epi64x(exps[3], exps[2], exps[1], exps[0]);
            auto col = vec4(signs >> col_offset, col_exps, col_mants);
            auto cell_result = dot(row, col);

            int result_offset = 4 * i + j;
            bool sign = cell_result.sign();
            out.signs = out.signs & ~(1 << result_offset) | (sign << result_offset);
            out.mantissas[result_offset] = cell_result.mantissa;
            out.exponents[result_offset] = cell_result.exponent;
        }
    }

    return out;
}

bf mat4::get(int i, int j) {
    int offset = 4 * i + j;
    return CONDITIONAL_INV((signs >> offset) & 1, bf(exponents[i], mantissas[i]));
}

template<bf f(bf a, bf b)>
inline void componentwise(mat4 &a, mat4 &b) {
}
