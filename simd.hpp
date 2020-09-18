#ifndef BIGFLOAT_SIMD_HPP
#define BIGFLOAT_SIMD_HPP

#include <xmmintrin.h>
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

#endif //BIGFLOAT_SIMD_HPP
