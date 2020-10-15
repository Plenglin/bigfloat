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
        col4& operator[](int i);

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
