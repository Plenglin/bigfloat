//
// Created by astrid on 10/8/20.
//

#include "mat4.hpp"
#include "vec4.hpp"
#include "helpers.inl"
#include <immintrin.h>

using namespace bigfloat;

mat4::mat4() = default;

mat4::mat4(bf m0, bf m1, bf m2, bf m3, bf m4, bf m5, bf m6, bf m7, bf m8, bf m9, bf m10, bf m11, bf m12, bf m13, bf m14,
           bf m15) : rows {
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
        0, 0, 0, d) {

}

mat4::mat4(bf x) : mat4(x, x, x, x) {

}

mat4::mat4(vec4 c0, vec4 c1, vec4 c2, vec4 c3) : rows{c0, c1, c2, c3} {

}

mat4::row &mat4::operator[](int i) {
    return rows[i];
}

mat4 mat4::T() {
    return mat4(
            rows[0][0], rows[0][1], rows[0][2], rows[0][3],
            rows[1][0], rows[1][1], rows[1][2], rows[1][3],
            rows[2][0], rows[2][1], rows[2][2], rows[2][3],
            rows[3][0], rows[3][1], rows[3][2], rows[3][3]
    );
}

mat4 mat4::inverted() {

}

void mat4::mul_componentwise(mat4 &other) {
    rows[0] *= other.rows[0];
    rows[1] *= other.rows[1];
    rows[2] *= other.rows[2];
    rows[3] *= other.rows[3];
}

void mat4::operator+=(mat4 &other) {
    rows[0] += other.rows[0];
    rows[1] += other.rows[1];
    rows[2] += other.rows[2];
    rows[3] += other.rows[3];
}

void mat4::operator-=(mat4 &other) {
    rows[0] -= other.rows[0];
    rows[1] -= other.rows[1];
    rows[2] -= other.rows[2];
    rows[3] -= other.rows[3];
}

mat4 mat4::operator+(mat4 &other) {
    return mat4(
            rows[0] + other.rows[0],
            rows[1] + other.rows[1],
            rows[2] + other.rows[2],
            rows[3] + other.rows[3]
            );
}

mat4 mat4::operator-(mat4 &other) {
    return mat4(
            rows[0] - other.rows[0],
            rows[1] - other.rows[1],
            rows[2] - other.rows[2],
            rows[3] - other.rows[3]
    );
}

mat4 mat4::operator*(mat4 &other) {
    mat4 out;
    mat4 &A = *this;
    for (int i = 0; i < 4; i++) {
        auto col = vec4(A[0][i], A[1][i], A[2][i], A[3][i]);
        bf acc[4];

        for (int j = 0; j < 4; j++) {
            acc[j] += dot(col, rows[j]);
        }

        out[i] = vec4(acc);
    }

    return out;
}

bool mat4::operator==(mat4 &other) {
    for (int i = 0; i < 4; i++) {
        if (rows[i] != other.rows[i]) {
            return false;
        }
    }
    return true;
}

template<bf f(bf a, bf b)>
inline void componentwise(mat4 &a, mat4 &b) {
}
