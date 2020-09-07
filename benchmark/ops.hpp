#ifndef BIGFLOAT_OPS_HPP
#define BIGFLOAT_OPS_HPP

#include <benchmark/benchmark.h>


#include "../bf.hpp"

using namespace bigfloat;

const static double as[] = {98127, 0.9123478, 9.923645, -2.834679, 1.134598, -98245.932458};
const static double bs[] = {1.1243e8, 84123.120734, -982314.238, -192, 9182.1234, 891.23456};

const static int count = sizeof(as) / sizeof(double);

static void bigfloat_addition(benchmark::State &state) {
    int i = 0;
    for (auto _ : state) {
        bf a(as[i % count]);
        bf b(bs[i++ % count]);
        volatile auto c = a + b;
    }
}

static void bigfloat_construction(benchmark::State &state) {
    for (auto _ : state) {
        volatile double x = 31.1234;
        volatile auto a = bf(x);
    }
}

static void bigfloat_multiplication(benchmark::State &state) {
    int i = 0;
    for (auto _ : state) {
        bf a(as[i % count]);
        bf b(bs[i++ % count]);
        volatile auto c = a * b;
    }
}

static void bigfloat_division(benchmark::State &state) {
    int i = 0;
    for (auto _ : state) {
        bf a(as[i % count]);
        bf b(bs[i++ % count]);
        volatile auto c = a / b;
    }
}

#endif //BIGFLOAT_OPS_HPP
