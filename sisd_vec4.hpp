//
// Created by astrid on 9/18/20.
//

#ifndef BIGFLOAT_SISD_VEC4_HPP
#define BIGFLOAT_SISD_VEC4_HPP

#include "bf.hpp"

namespace bigfloat::simd {
    struct sisd_vec4 {
        bf xs[4];

        explicit sisd_vec4(bf x);
        sisd_vec4(const bf &x0, const bf &x1, const bf &x2, const bf &x3);

        bf operator[](int i) const;
        void invert();
        void negate();
        void operator+=(sisd_vec4 &other);
        void operator-=(sisd_vec4 &other);
        void operator*=(sisd_vec4 &other);
        void operator/=(sisd_vec4 &other);
    };

    std::ostream &operator<<(std::ostream &os, const sisd_vec4 &x);
}

#endif //BIGFLOAT_SISD_VEC4_HPP
