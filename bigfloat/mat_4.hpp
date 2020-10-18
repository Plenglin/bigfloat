//
// Created by astrid on 10/8/20.
//

#ifndef BIGFLOAT_MAT_4_HPP
#define BIGFLOAT_MAT_4_HPP

#include "bf.hpp"

namespace bigfloat {
    class bf_ref {};

    class col4 {};

    class mat4 {
        // Column-major
        int signs;
        short exponents[16];
        unsigned long mantissas[16];
    public:
        mat4();

        // Create a scaling matrix (I * x)
        mat4(bf x);
        // Create a diagonal matrix, with a, b, c, and d as the diagonal values.
        mat4(bf a, bf b, bf c, bf d);
        mat4(bf m0, bf m1, bf m2, bf m3, bf m4, bf m5, bf m6, bf m7, bf m8, bf m9, bf m10, bf m11, bf m12, bf m13, bf m14, bf m15);
        bf get(int i, int j);

        void operator+=(mat4 &other);
        void operator-=(mat4 &other);
        mat4 operator+(mat4 &other);
        mat4 operator-(mat4 &other);
        void mul_componentwise(mat4 &other);

        mat4 operator*(mat4 &other);

        void transpose();
        void invert();
    };
}


#endif //BIGFLOAT_MAT_4_HPP
