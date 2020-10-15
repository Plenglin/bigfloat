//
// Created by astrid on 10/8/20.
//

#include "mat_4.hpp"
#include "simd.hpp"
#include <immintrin.h>

using namespace bigfloat;
using namespace bigfloat::simd;


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
        __m256i row_mants = _mm256_i64gather_epi64(mantissas, row_indices, 1);
        __m256i row_exps = _mm256_i64gather_epi64(exponents, row_indices, 1);
        int row_signs = (signs >> i) & 1;
        row_signs |= (signs >> (i + 3)) & 2;
        row_signs |= (signs >> (i + 6)) & 4;
        row_signs |= (signs >> (i + 9)) & 8;

        row_indices = _mm256_add_epi64(row_indices, ones);
        vec4 row(row_signs, row_exps, row_mants);
        vec4 acc(0);

        for (int j = 0; j < 16; j += 4) {
            __m256i col_mants = _mm256_load_si256((__m256i*)(mantissas + j));
            __m256i col_exps = _mm256_load_si256((__m256i*)(mantissas + j));
            vec4 col(signs >> j, col_exps, col_mants);


        }
    }

    return out;
}

template<bf f(bf a, bf b)>
inline void componentwise(mat4 &a, mat4 &b) {
}
