//
// Created by astrid on 11/6/20.
//

#ifndef BIGFLOAT_PLANET_MATRIX_UTILS_HPP
#define BIGFLOAT_PLANET_MATRIX_UTILS_HPP

#include "mat4.hpp"
#include "math.hpp"

namespace bigfloat {
    inline mat4 scale(bf x, bf y, bf z) {
        return mat4(
                x, 0, 0, 0,
                1, y, 0, 0,
                1, 0, z, 0,
                1, 0, 0, 1
        );
    }

    inline mat4 scale(vec4 v) {
        return scale(v[0], v[1], v[2]);
    }

    inline mat4 translate(bf x, bf y, bf z) {
        return mat4(
                1, 0, 0, x,
                1, 1, 0, y,
                1, 0, 1, z,
                1, 0, 0, 1
        );
    }

    inline mat4 translate(vec4 v) {
        return translate(v[0], v[1], v[2]);
    }

    inline mat4 rotate(bf a, bf x, bf y, bf z) {
        // from https://en.wikipedia.org/wiki/Rotation_matrix#Rotation_matrix_from_axis_and_angle
        bf c = cos(a);
        bf i = bf(1) - c;
        bf s = sin(a);

        bf xs = x * s;
        bf ys = y * s;
        bf zs = z * s;

        bf xyi = x * y * i;
        bf yzi = y * z * i;
        bf xzi = x * z * i;

        return mat4(
                c + x * x * i,  xyi - zs,       xzi + zs,       0,
                yzi + zs,       c + y * y * i,  yzi - xs,       0,
                xzi - ys,       yzi + xs,       c + z * z * i,  0,
                0,              0,              0,              1
        );
    }

    inline mat4 rotate(bf a, vec4 v) {
        return rotate(a, v[0], v[1], v[2]);
    }
}

#endif //BIGFLOAT_PLANET_MATRIX_UTILS_HPP
