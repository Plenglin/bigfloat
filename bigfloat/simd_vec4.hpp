#ifndef BIGFLOAT_SIMD_VEC4_HPP
#define BIGFLOAT_SIMD_VEC4_HPP

#include <immintrin.h>
#include "bf.hpp"


namespace bigfloat {

    struct simd_vec4 {
        union {
            __m256i mantissa;
            unsigned long mantissa_array[4];
        };
        union {
            // Although exponents are still 16 bits, this is more efficient for computation.
            __m256i exponent;
            long exponent_array[4];
        };
        int sign;

        simd_vec4();
        explicit simd_vec4(bf x);
        explicit simd_vec4(bf *x);
        simd_vec4(int sign, __m256i exponent, __m256i mantissa);
        simd_vec4(const bf &x0, const bf &x1, const bf &x2, const bf &x3);
        explicit simd_vec4(__m256d x);
        explicit operator __m256d() const;

        bf operator[](int i) const;
        void invert();
        void negate();
        simd_vec4 operator-() const;

        simd_vec4 operator+(simd_vec4 &other) const;
        simd_vec4 operator-(simd_vec4 &other) const;
        simd_vec4 operator*(simd_vec4 &other);
        simd_vec4 operator/(simd_vec4 &other);

        void operator+=(simd_vec4 &other);
        void operator-=(simd_vec4 &other);
        void operator*=(simd_vec4 &other);
        void operator/=(simd_vec4 &other);

        bool operator==(simd_vec4 &other);
        bool operator!=(simd_vec4 &other);
    };

    bf dot(simd_vec4 &a, simd_vec4 &b);
    std::ostream &operator<<(std::ostream &os, const simd_vec4 &x);
}
#endif //BIGFLOAT_SIMD_VEC4_HPP
