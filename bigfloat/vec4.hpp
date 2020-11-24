#ifndef BIGFLOAT_VEC4_HPP
#define BIGFLOAT_VEC4_HPP

#include <xmmintrin.h>
#include <vector>
#include <memory>
#include "bf.hpp"


#ifdef __AVX2__
#pragma message "AVX2 detected! Using SIMD instructions for accelerated arithmetic."

#include "simd_vec4.hpp"
namespace bigfloat {
    typedef simd_vec4 vec4;
}

#else

#include "sisd_vec4.hpp"
namespace bigfloat {
    typedef sisd_vec4 vec4;
}
#endif

namespace bigfloat {
}

#endif //BIGFLOAT_VEC4_HPP
