#include "math.hpp"
#include "cmath"

using namespace bigfloat;

bf math::sqrt(const bf x) {
    if (x.sign()) return bf::nan(false);

    // Double-impl guess gives us 52 bits.
    auto guess = bf(std::sqrt(double(x)));

    // Single step of the Babylonian method, which converges quadratically, gives us 104 bits.
    auto secondary = x / guess;
    return (guess + secondary) / 2;
}

bf math::exp(const bf x) {
    return bf();
}

bf math::log(const bf x) {
    return bf();
}

bf math::sin(const bf x) {
    return bf();
}

bf math::cos(const bf x) {
    return bf();
}