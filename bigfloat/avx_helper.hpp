#ifndef BIGFLOAT_AVX_HELPER_HPP
#define BIGFLOAT_AVX_HELPER_HPP


#include <xmmintrin.h>
#include <immintrin.h>

#define MKUNC_MSB 1UL << 62

namespace bigfloat::helper {
    union m256_union {
        unsigned int i[8];
        unsigned long q[4];
        __m256i v;
    };

    inline unsigned long multiply_keep_upper_no_carry(unsigned long a, unsigned long b) {
        unsigned __int128 mul = (unsigned __int128)a * (unsigned __int128)b;
        unsigned long upper = mul >> 64;
        upper >>= (upper >> 63);
        return upper;
    }

    inline __m256i multiply_keep_upper_no_carry(__m256i a, __m256i b) {
        // HTL vectors
        __m256i a1 = _mm256_srli_epi64(a, 32);
        __m256i b1 = _mm256_srli_epi64(b, 32);

        // Perform multiplications and add together
        __m256i a1b1 = _mm256_mul_epu32(a1, b1);
        __m256i a1b0 = _mm256_mul_epu32(a1, b);
        a1b0 = _mm256_srli_epi64(a1b0, 32);
        __m256i sum = _mm256_add_epi64(a1b1, a1b0);

        __m256i a0b1 = _mm256_mul_epu32(a, b1);
        a0b1 = _mm256_srli_epi64(a0b1, 32);
        sum = _mm256_add_epi64(sum, a0b1);

        // Correct for MSB position
        __m256i has_upper_bit_mask = _mm256_srai_epi32(sum, 31);
        has_upper_bit_mask = (__m256i)_mm256_permute_ps((__m256)has_upper_bit_mask, 0b11011101);
        __m256i sum_sr = _mm256_srli_epi64(sum, 1);
        __m256i sum_corrected = _mm256_blendv_epi8(sum, sum_sr, has_upper_bit_mask);

        return sum_corrected;
    }

    inline __m256i conditional_negate(__m256i sign, __m256i val) {
        __m256i sub1 = _mm256_add_epi64(val, sign);
        return _mm256_xor_si256(sub1, sign);
    }
}

#endif //BIGFLOAT_AVX_HELPER_HPP
