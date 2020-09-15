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

static void bigfloat_division(benchmark::State &state) {
    int i = 0;
    bf a, b;
    for (auto _ : state) {
        a = bf_as[i % NUMBERS_COUNT];
        b = bf_bs[i++ % NUMBERS_COUNT];
        volatile auto c = a / b;
    }
}

#endif //BIGFLOAT_OPS_HPP
