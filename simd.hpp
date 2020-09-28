#ifndef BIGFLOAT_SIMD_HPP
#define BIGFLOAT_SIMD_HPP

#include <xmmintrin.h>
#include <vector>
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
        std::vector<vec4> vecs;
    public:
        explicit vecn(const std::vector<bf>& xs);
        bf operator[](int i) const;
        void invert();
        void negate();
        void operator+=(vecn &other);
        void operator-=(vecn &other);
        void operator*=(vecn &other);
        void operator/=(vecn &other);
    };
}

#endif //BIGFLOAT_SIMD_HPP
