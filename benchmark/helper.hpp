#ifndef BIGFLOAT_HELPER_HPP
#define BIGFLOAT_HELPER_HPP

#include <benchmark/benchmark.h>

#include "../avx_helper.hpp"


using namespace bigfloat::helper;

static void simd_mkunc(benchmark::State &state) {
    volatile __m256i v = _mm256_set_epi64x(823789 | MKUNC_MSB, 8124671263 | MKUNC_MSB, 67812589 | MKUNC_MSB, 2368749523 | MKUNC_MSB);
    for (auto _ : state) {
        v = multiply_keep_upper_no_carry(v, v);
    }
}

#endif //BIGFLOAT_HELPER_HPP
