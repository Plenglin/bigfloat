#ifndef BIGFLOAT_HELPER_HPP
#define BIGFLOAT_HELPER_HPP

#include <benchmark/benchmark.h>

#include "../avx_helper.hpp"


using namespace bigfloat::helper;

static void simd_mkunc(benchmark::State &state) {
    __m256i v = _mm256_set_epi64x(823789 | MKUNC_MSB, 8124671263 | MKUNC_MSB, 67812589 | MKUNC_MSB, 2368749523 | MKUNC_MSB);
    for (auto _ : state) {
        v = multiply_keep_upper_no_carry(v, v);
    }
    volatile __m256i result = v;
}

static void simd_int32x8_multiply(benchmark::State &state) {
    __m256i v = _mm256_set_epi64x(823789 | MKUNC_MSB, 8124671263 | MKUNC_MSB, 67812589 | MKUNC_MSB, 2368749523 | MKUNC_MSB);
    for (auto _ : state) {
        v = _mm256_mul_epu32(v, v);
    }
    benchmark::DoNotOptimize(v);
}

static void sisd_int32x8_multiply(benchmark::State &state) {
    int a = 824671263 | (1 << 30);
    int b = 67812589 | (1 << 30);
    int c = 84671263 | (1 << 30);
    int d = 67812589 | (1 << 30);
    for (auto _ : state) {
        benchmark::DoNotOptimize(a *= d);
        benchmark::DoNotOptimize(b *= c);
        benchmark::DoNotOptimize(a *= d);
        benchmark::DoNotOptimize(b *= c);
        benchmark::DoNotOptimize(a *= d);
        benchmark::DoNotOptimize(b *= c);
        benchmark::DoNotOptimize(a *= d);
        benchmark::DoNotOptimize(b *= c);
    }
    benchmark::DoNotOptimize(a);
}

#endif //BIGFLOAT_HELPER_HPP
