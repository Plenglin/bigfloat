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

void simd::mul_2(bf *a, bf *b) {
#ifdef __AVX__
    // TODO
#else
    a[0] *= b[0];
    a[1] *= b[1];
#endif
}
