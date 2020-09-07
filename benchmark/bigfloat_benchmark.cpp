#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
#include <benchmark/benchmark.h>
#include "../bf.hpp"

using namespace bigfloat;

const static double as[] = {98127, 0.9123478, 9.923645, -2.834679, 1.134598, -98245.932458};
const static double bs[] = {1.1243e8, 84123.120734, -982314.238, -192, 9182.1234, 891.23456};

const static int count = sizeof(as) / sizeof(double);

static void bigfloat_addition(benchmark::State& state) {
    int i = 0;
    for (auto _ : state) {
        bf a(as[i % count]);
        bf b(bs[i++ % count]);
        volatile auto c = a + b;
    }
}
BENCHMARK(bigfloat_addition);

static void double_addition(benchmark::State& state) {
    for (auto _ : state) {
        double a = 31.1234;
        volatile double b = 31.1234;
        volatile double c = a + b;
    }
}
BENCHMARK(double_addition);

static void bigfloat_construction(benchmark::State& state) {
    for (auto _ : state) {
        volatile double x = 31.1234;
        volatile auto a = bf(x);
    }
}
BENCHMARK(bigfloat_construction);

static void bigfloat_multiplication(benchmark::State& state) {
    int i = 0;
    for (auto _ : state) {
        bf a(as[i % count]);
        bf b(bs[i++ % count]);
        volatile auto c = a * b;
    }
}
BENCHMARK(bigfloat_multiplication);

static void double_multiplication(benchmark::State& state) {
    for (auto _ : state) {
        double a = 31.1234;
        volatile double b = 31.1234;
        volatile double c = a * b;
    }
}
BENCHMARK(double_multiplication);

static void bigfloat_division(benchmark::State& state) {
    int i = 0;
    for (auto _ : state) {
        bf a(as[i % count]);
        bf b(bs[i++ % count]);
        volatile auto c = a / b;
    }
}
BENCHMARK(bigfloat_division);

static void double_division(benchmark::State& state) {
    for (auto _ : state) {
        double a = 31.1234;
        volatile double b = 123.812346;
        volatile double c = a / b;
    }
}
BENCHMARK(double_division);

static void int128_division(benchmark::State& state) {
    for (auto _ : state) {
        __int128 a = (__int128)31231 << 64;
        volatile __int128 b = 3129389;
        volatile __int128 c = a / b;
    }
}
BENCHMARK(int128_division);

static void int64_division(benchmark::State& state) {
    for (auto _ : state) {
        long a = (long)31231 << 32;
        volatile long b = 3129389;
        volatile long c = a / b;
    }
}
BENCHMARK(int64_division);

static void int32_division(benchmark::State& state) {
    for (auto _ : state) {
        int a = 931212343;
        volatile int b = 12;
        volatile int c = a / b;
    }
}
BENCHMARK(int32_division);

BENCHMARK_MAIN();
#pragma clang diagnostic pop