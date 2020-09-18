#ifndef BIGFLOAT_HELPER_HPP
#define BIGFLOAT_HELPER_HPP

#include <benchmark/benchmark.h>

#include "../avx_helper.hpp"

static void multiply_keep_upper_no_carry(benchmark::State &state) {
    for (auto _ : state) {
        long a = 31231L << 32;
        volatile long b = 3129389;
        volatile long c = bigfloat::helper::multiply_keep_upper_no_carry(a, b);
    }
}

#endif //BIGFLOAT_HELPER_HPP
