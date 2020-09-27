#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <benchmark/benchmark.h>
#include "control.hpp"
#include "ops.hpp"
#include "advanced.hpp"
#include "bench_simd.h"

BENCHMARK(bigfloat_construction);

BENCHMARK(bigfloat_addition);
BENCHMARK(double_addition);
BENCHMARK(bigfloatx4_additionx2);

BENCHMARK(bigfloat_multiplication);
BENCHMARK(double_multiplication);
BENCHMARK(bigfloatx4_multiplication);
BENCHMARK(doublex4_multiplication);

BENCHMARK(bigfloat_division_slow);
BENCHMARK(bigfloat_division_fast);
BENCHMARK(double_division);
BENCHMARK(int128_division);
BENCHMARK(int64_division);
BENCHMARK(int32_division);

BENCHMARK(bigfloat_nbody);
BENCHMARK(double_nbody);

BENCHMARK_MAIN();

#pragma clang diagnostic pop