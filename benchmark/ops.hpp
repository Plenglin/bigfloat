#ifndef BIGFLOAT_OPS_HPP
#define BIGFLOAT_OPS_HPP

#include <benchmark/benchmark.h>


#include "shared.hpp"

static void bigfloat_addition(benchmark::State &state) {
    int i = 0;
    bf a, b;
    for (auto _ : state) {
        a = bf_as[i % NUMBERS_COUNT];
        b = bf_bs[i++ % NUMBERS_COUNT];
        volatile auto c = a + b;
    }
}

static void bigfloat_construction(benchmark::State &state) {
    int i = 0;
    for (auto _ : state) {
        volatile double x = d_as[i++ % NUMBERS_COUNT];
        volatile auto a = bf(x);
    }
}

static void bigfloat_multiplication(benchmark::State &state) {
    int i = 0;
    bf a, b;
    for (auto _ : state) {
        a = bf_as[i % NUMBERS_COUNT];
        b = bf_bs[i++ % NUMBERS_COUNT];
        volatile auto c = a * b;
    }
}

static void bigfloat_division_slow(benchmark::State &state) {
    int i = 0;
    bf a, b;
    for (auto _ : state) {
        a = bf_as[i % NUMBERS_COUNT];
        b = bf_bs[i++ % NUMBERS_COUNT];
        volatile auto c = a.slow_div(b);
    }
}

static void bigfloat_division_fast(benchmark::State &state) {
    int i = 0;
    bf a, b;
    for (auto _ : state) {
        a = bf_as[i % NUMBERS_COUNT];
        b = bf_bs[i++ % NUMBERS_COUNT];
        volatile auto c = a.fast_div(b);
    }
}

#endif //BIGFLOAT_OPS_HPP
