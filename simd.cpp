#include "simd.hpp"

#include "bf.hpp"
#include <immintrin.h>

#ifdef __AVX512__
#pragma message "AVX512 is enabled."
#else
#ifdef __AVX2__
#warning "AVX512 is not enabled. Deferring to AVX2 instructions for vectorization."
#else
#ifdef __AVX__
#warning "AVX2, AVX512 are not enabled. Deferring to AVX instructions for vectorization."
#else
#warning "None of AVX, AVX2, AVX512 are enabled. No vectorization is possible! Deferring to SISD instructions."
#endif
#endif
#endif

using namespace bigfloat;


inline bf mult_impl(bool sign, int exa, unsigned long mta, int exb, unsigned long mtb) {
    // Multiply mantissas
    unsigned __int128 mul = (unsigned __int128)mta * (unsigned __int128)mtb;

    // Extract leading zeros
    unsigned long result_upper = mul >> 64;
    int leading_zeros = __builtin_clzl(result_upper);

    // Normalize exponent and mantissa
    unsigned long mto = mul >> (64 - leading_zeros);
    int exo = exa + exb - leading_zeros - 1022;  // Bias - 1

    return bf(sign, exo, mto);
}

void simd::mul_2(bf *a, bf *b) {
#ifdef __AVX__
    //__m128 mta = __mm
#else
    a[0] *= b[0];
    a[1] *= b[1];
#endif
}
