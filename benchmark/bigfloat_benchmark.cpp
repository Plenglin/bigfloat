#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
#include <benchmark/benchmark.h>
#include "../bf.hpp"

using namespace bigfloat;

static void bigfloat_addition(benchmark::State& state) {
    for (auto _ : state) {
        bf a(32.31);
        bf b(831.1329);
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
    for (auto _ : state) {
        bf a(32.31);
        bf b(831.1329);
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
    for (auto _ : state) {
        bf a(32.31);
        bf b(831.1329);
        volatile auto c = a / b;
    }
}
BENCHMARK(bigfloat_division);

static void double_division(benchmark::State& state) {
    for (auto _ : state) {
        double a = 31.1234;
        volatile double b = 31.1234;
        volatile double c = a / b;
    }
}
BENCHMARK(double_division);

BENCHMARK_MAIN();
#pragma clang diagnostic pop