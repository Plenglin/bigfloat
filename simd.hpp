#ifndef BIGFLOAT_SIMD_HPP
#define BIGFLOAT_SIMD_HPP

#include <xmmintrin.h>
#include <vector>
#include <memory>
#include "bf.hpp"


#ifdef __AVX2__
#pragma message "AVX2 detected! Using SIMD instructions for accelerated arithmetic."

#include "simd_vec4.hpp"
namespace bigfloat::simd {
    typedef simd_vec4 vec4;
}

#else
#warning "AVX2 is not enabled! No vectorization is possible, Deferring to SISD instructions."

#include "sisd_vec4.hpp"
namespace bigfloat::simd {
    typedef sisd_vec4 vec4;
}
#endif

namespace bigfloat::simd {
    class vecn {
        size_t count;
        unsigned long *mantissa;
        long *exponent;
        char *sign;
    public:
        explicit vecn(size_t count);
        explicit vecn(std::vector<bf> vecs);
        ~vecn();

        bf operator[](int offset) const;
        vec4 get_vec(int offset) const;
        vec4 set_vec(int offset, vec4 &v);
        void invert();
        void negate();
        void operator+=(vecn &other);
        void operator-=(vecn &other);
        void operator*=(vecn &other);
        void operator/=(vecn &other);
    };
}

#endif //BIGFLOAT_SIMD_HPP
