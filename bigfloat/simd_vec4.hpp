#ifndef BIGFLOAT_SIMD_VEC4_HPP
#define BIGFLOAT_SIMD_VEC4_HPP

#include <immintrin.h>
#include "bf.hpp"
#include "helpers.inl"


namespace bigfloat {

    struct bf_ref;

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
        unsigned int sign;

        simd_vec4();
        explicit simd_vec4(bf x);
        explicit simd_vec4(bf *x);
        simd_vec4(int sign, __m256i exponent, __m256i mantissa);
        simd_vec4(const bf &x0, const bf &x1, const bf &x2, const bf &x3);
        explicit simd_vec4(__m256d x);
        explicit operator __m256d() const;

        bf_ref operator[](int i) const;
        void invert();
        void negate();
        simd_vec4 operator-() const;

        simd_vec4 operator+(simd_vec4 &other) const;
        simd_vec4 operator-(simd_vec4 &other) const;
        simd_vec4 operator*(simd_vec4 &other) const;
        simd_vec4 operator/(simd_vec4 &other) const;

        simd_vec4 operator+(bf other) const;
        simd_vec4 operator-(bf other) const;
        simd_vec4 operator*(bf other) const;
        simd_vec4 operator/(bf other) const;

        simd_vec4 operator+(bf_ref other) const;
        simd_vec4 operator-(bf_ref other) const;
        simd_vec4 operator*(bf_ref other) const;
        simd_vec4 operator/(bf_ref other) const;

        void operator+=(simd_vec4 &other);
        void operator-=(simd_vec4 &other);
        void operator*=(simd_vec4 &other);
        void operator/=(simd_vec4 &other);

        bool operator==(simd_vec4 &other);
        bool operator!=(simd_vec4 &other);
    };

    struct bf_ref {
        simd_vec4 *parent;
        int i;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "google-explicit-constructor"
        inline operator bf() const {
            auto ex = parent->exponent[i];
            auto mt = parent->mantissa[i];
            mt = CONDITIONAL_INV(parent->sign >> i & 1, mt);
            return bf(ex, mt);
        }
#pragma clang diagnostic pop

        inline void operator&=(bf other) const {
            parent->mantissa_array[i] = other.mantissa;
            parent->exponent[i] = other.mantissa;
            parent->sign = other.mantissa;
        }

        inline bf_ref& operator=(bf other) {
            parent->mantissa_array[i] = other.mantissa;
            parent->exponent[i] = other.mantissa;
            parent->sign = other.mantissa;
            return *this;
        }
    };

    bf dot(simd_vec4 &a, simd_vec4 &b);
    std::ostream &operator<<(std::ostream &os, const simd_vec4 &x);
}
#endif //BIGFLOAT_SIMD_VEC4_HPP
