#ifndef BIGFLOAT_CONTROL_HPP
#define BIGFLOAT_CONTROL_HPP

#include <benchmark/benchmark.h>
#include "shared.hpp"
#include "../avx_helper.hpp"

static void double_addition(benchmark::State &state) {
    int i = 0;
    double a, b;
    for (auto _ : state) {
        a = d_as[i % NUMBERS_COUNT];
        b = d_bs[i++ % NUMBERS_COUNT];
        volatile auto c = a + b;
    }
}

static void double_multiplication(benchmark::State &state) {
    int i = 0;
    double a, b;
    for (auto _ : state) {
        a = d_as[i % NUMBERS_COUNT];
        b = d_bs[i++ % NUMBERS_COUNT];
        volatile auto c = a * b;
    }
}

static void double_division(benchmark::State &state) {
    for (auto _ : state) {
        double a = 31.1234;
        volatile double b = 123.812346;
        volatile double c = a / b;
    }
}

static void int128_division(benchmark::State &state) {
    for (auto _ : state) {
        __int128 a = (__int128)31231 << 64;
        volatile __int128 b = 3129389;
        volatile __int128 c = a / b;
    }
}

static void int64_division(benchmark::State &state) {
    for (auto _ : state) {
        long a = (long)31231 << 32;
        volatile long b = 3129389;
        volatile long c = a / b;
    }
}

static void int32_division(benchmark::State &state) {
    for (auto _ : state) {
        int a = 931212343;
        volatile int b = 12;
        volatile int c = a / b;
    }
}

static void sisd_mkunc(benchmark::State &state) {
    for (auto _ : state) {
        unsigned long a = 3191236748126UL | MKUNC_MSB;
        volatile unsigned long b = 12391236748126UL | MKUNC_MSB;
        volatile unsigned long c = bigfloat::helper::multiply_keep_upper_no_carry(a, b);
    }
}

#endif //BIGFLOAT_CONTROL_HPP
