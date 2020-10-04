//
// Created by astrid on 9/7/20.
//

#ifndef BIGFLOAT_BENCHMARK_NBODY_UTIL_HPP
#define BIGFLOAT_BENCHMARK_NBODY_UTIL_HPP

#include <type_traits>
#include <math.h>
#include "../../include/bf.hpp"
#include "../../include/math.hpp"

template<typename real>
real t_sqrt(real x) {
    using namespace bigfloat::math;
    return sqrt(x);
}

#endif //BIGFLOAT_BENCHMARK_NBODY_UTIL_HPP
