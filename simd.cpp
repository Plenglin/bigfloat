#include "simd.hpp"

#include "bf.hpp"
#include <immintrin.h>

#ifndef __AVX512__
#ifndef __AVX2__
#ifndef __AVX__
#warning "None of AVX, AVX2, AVX512 are enabled. No vectorization is possible! Deferring to SISD instructions."
#else
#warning "AVX2, AVX512 are not enabled. Deferring to AVX instructions for vectorization."
#endif
#else
#warning "AVX512 is not enabled. Deferring to AVX2 instructions for vectorization."
#endif
#else
#pragma message "AVX512 is enabled."
#endif

using namespace bigfloat;

void simd::mul_2(bf *a, bf *b) {
#ifndef __AVX__
    a[0] *= b[0];
    a[1] *= b[1];
#else
    // TODO
#endif
}
