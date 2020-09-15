#include "math.hpp"

using namespace bigfloat;

bf math::sqrt(bf x) {
    return bf(x.exponent / 2, x.mantissa);
}

bf math::log(bf x) {
    return bf();
}

bf math::sin(bf x) {
    return bf();
}

bf math::cos(bf x) {
    return bf();
}