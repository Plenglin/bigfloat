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
    std::ostream &operator<<(std::ostream &os, const vec4 &x) {
        os << "[" << x[0] << "," << x[1] << "," << x[2] << "," << x[3] << "]";
        return os;
    }

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

#endif //BIGFLOAT_VEC4_HPP
