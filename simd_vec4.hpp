#ifndef BIGFLOAT_SIMD_VEC4_HPP
#define BIGFLOAT_SIMD_VEC4_HPP

#include <immintrin.h>
#include "bf.hpp"


namespace bigfloat::simd {

    struct vec4 {
        __m256i mantissa;
        __m256i exponent;
        int sign;

        vec4(bf x0, bf x1, bf x2, bf x3);
        bf operator[](int i) const;
        void operator+=(vec4 &other);
        void operator*=(vec4 &other);
    };

    std::ostream &operator<<(std::ostream &os, const vec4 &x);
}
#endif //BIGFLOAT_SIMD_VEC4_HPP
