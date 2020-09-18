#ifndef BIGFLOAT_SIMD_VEC4_HPP
#define BIGFLOAT_SIMD_VEC4_HPP

#include <immintrin.h>
#include "bf.hpp"


namespace bigfloat::simd {

    struct simd_vec4 {
        __m256i mantissa;
        __m256i exponent;
        int sign;

        explicit simd_vec4(bf x);
        simd_vec4(bf x0, bf x1, bf x2, bf x3);

        bf operator[](int i) const;
        void invert();
        void negate();
        void operator+=(simd_vec4 &other);
        void operator-=(simd_vec4 &other);
        void operator*=(simd_vec4 &other);
        void operator/=(simd_vec4 &other);
    };

    std::ostream &operator<<(std::ostream &os, const simd_vec4 &x);
}
#endif //BIGFLOAT_SIMD_VEC4_HPP
