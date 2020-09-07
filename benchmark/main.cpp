#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <benchmark/benchmark.h>
#include "./control.hpp"
#include "./ops.hpp"

BENCHMARK(bigfloat_construction);

BENCHMARK(bigfloat_addition);
BENCHMARK(double_addition);

BENCHMARK(bigfloat_multiplication);
BENCHMARK(double_multiplication);

BENCHMARK(bigfloat_division);
BENCHMARK(double_division);
BENCHMARK(int128_division);
BENCHMARK(int64_division);
BENCHMARK(int32_division);

BENCHMARK_MAIN();

#pragma clang diagnostic pop