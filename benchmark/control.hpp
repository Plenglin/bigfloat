#ifndef BIGFLOAT_CONTROL_HPP
#define BIGFLOAT_CONTROL_HPP

#include <benchmark/benchmark.h>

static void double_addition(benchmark::State &state) {
    for (auto _ : state) {
        double a = 31.1234;
        volatile double b = 31.1234;
        volatile double c = a + b;
    }
}

static void double_multiplication(benchmark::State &state) {
    for (auto _ : state) {
        double a = 31.1234;
        volatile double b = 31.1234;
        volatile double c = a * b;
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

#endif //BIGFLOAT_CONTROL_HPP
