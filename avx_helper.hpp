#ifndef BIGFLOAT_AVX_HELPER_HPP
#define BIGFLOAT_AVX_HELPER_HPP


#include <xmmintrin.h>
#include <immintrin.h>

namespace bigfloat::helper {
    union m128_union {
        unsigned int i[4];
        unsigned long q[2];
        __m128i v;
    };
    inline unsigned long multiply_keep_upper_no_carry(unsigned long a, unsigned long b) {
        m128_union prods;

        __m128i vab = _mm_set_epi64x(a, b);
        m128_union va1b1;
        va1b1.v = _mm_srli_epi64(vab, 32);

        __m128i vb0a0 = _mm_set_epi32(0, b, 0, a);
        prods.v = _mm_mul_epu32(va1b1.v, vb0a0);

        unsigned long upper_prod = va1b1.q[0] * va1b1.q[1];
        unsigned long sum = upper_prod;
        sum += prods.i[1];
        sum += prods.i[3];

        return sum;
    }
}

#endif //BIGFLOAT_AVX_HELPER_HPP
