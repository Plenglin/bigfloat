#ifndef BIGFLOAT_ADVANCED_HPP
#define BIGFLOAT_ADVANCED_HPP

#include <benchmark/benchmark.h>
#include <bigfloat/bigfloat.hpp>

#include "nbody/nbody_sisd.hpp"

using namespace bigfloat;

static void bigfloat_nbody(benchmark::State &state) {
    nbody_bf_simd<bf> sim;
    for (auto _ : state) {
        sim.step(bf(1));
    }
}

static void double_nbody(benchmark::State &state) {
    nbody_bf_simd<double> sim;
    for (auto _ : state) {
        sim.step(1);
    }
}

#endif //BIGFLOAT_ADVANCED_HPP
