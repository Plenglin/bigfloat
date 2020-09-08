#ifndef BIGFLOAT_SIMD_VEC2_HPP
#define BIGFLOAT_SIMD_VEC2_HPP

#include <xmmintrin.h>
#include "bf.hpp"


namespace bigfloat::simd {

    struct vec2 {
        __m128i mantissa;
        __m128i exponent;
        int sign;

        vec2(bf x0, bf x1);
        bf operator[](int i);
        void operator+=(vec2 &other);
        void operator*=(vec2 &other);
    };

}
#endif //BIGFLOAT_SIMD_VEC2_HPP
