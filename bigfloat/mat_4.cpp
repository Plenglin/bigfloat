//
// Created by astrid on 10/8/20.
//

#include "mat_4.hpp"
#include "simd.hpp"
#include "helpers.inl"
#include <immintrin.h>

using namespace bigfloat;
using namespace bigfloat::simd;

mat4::mat4() = default;

mat4::mat4(bf m0, bf m1, bf m2, bf m3, bf m4, bf m5, bf m6, bf m7, bf m8, bf m9, bf m10, bf m11, bf m12, bf m13, bf m14,
           bf m15) : cols {
                                            vec4(m0, m1, m2, m3),
                                            vec4(m4, m5, m6, m7),
                                            vec4(m8, m9, m10, m11),
                                            vec4(m12, m13, m14, m15)
           } {
}


mat4::mat4(bf a, bf b, bf c, bf d) :    mat4(
        a, 0, 0, 0,
        0, b, 0, 0,
        0, 0, c, 0,
        0, 0, 0, d)
{ }

mat4::mat4(bf x) : mat4(x, x, x, x)
{ }

mat4::col &mat4::operator[](int i) {
    return cols[i];
}

void mat4::transpose() {

}

void mat4::invert() {

}

void mat4::mul_componentwise(mat4 &other) {

}

void mat4::operator+=(mat4 &other) {

}

void mat4::operator-=(mat4 &other) {

}

mat4 mat4::operator+(mat4 &other) {
    return mat4();
}

mat4 mat4::operator-(mat4 &other) {
    return mat4();
}

mat4 mat4::operator*(mat4 &other) {
    mat4 out;
    mat4 &A = *this;
    for (int i = 0; i < 4; i++) {
        auto row = vec4(A[0][i], A[1][i], A[2][i], A[3][i]);
        bf acc[4];

        for (int j = 0; j < 4; j++) {
            acc[j] += dot(row, cols[j]);
        }

        out[i] = vec4(acc);
    }

    return out;
}

template<bf f(bf a, bf b)>
inline void componentwise(mat4 &a, mat4 &b) {
}
