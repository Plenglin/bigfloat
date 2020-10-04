//
// Created by astrid on 9/19/20.
//

#ifndef BIGFLOAT_BENCH_SIMD_H
#define BIGFLOAT_BENCH_SIMD_H


#include <benchmark/benchmark.h>
#include "shared.hpp"
#include "simd_vec4.hpp"

using namespace bigfloat::simd;

static void bigfloatx4_multiplication(benchmark::State &state) {
    simd_vec4 vec(bf(91234), bf(83.3123789), bf(1728781.1237), bf(134289));
    for (auto _ : state) {
        vec *= vec;
    }
}

static void bigfloatx4_additionx2(benchmark::State &state) {
    simd_vec4 vec(bf(91234), bf(-83.3123789), bf(1728781.1237), bf(-134289));
    simd_vec4 vec1(bf(-2334), bf(1.3123789), bf(1728781.1237), bf(-134289));
    for (auto _ : state) {
        vec1 += vec;
        vec += vec1;
    }
    benchmark::DoNotOptimize(vec);
    benchmark::DoNotOptimize(vec1);
}

#endif //BIGFLOAT_BENCH_SIMD_H
