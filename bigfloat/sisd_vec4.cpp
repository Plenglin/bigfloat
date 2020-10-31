//
// Created by astrid on 9/18/20.
//

#include "sisd_vec4.hpp"

using namespace bigfloat;


sisd_vec4::sisd_vec4(bf x) : sisd_vec4(x, x, x, x) {

}

sisd_vec4::sisd_vec4(const bf &x0, const bf &x1, const bf &x2, const bf &x3) {
    xs[0] = x0;
    xs[1] = x1;
    xs[2] = x2;
    xs[3] = x3;
}

bf sisd_vec4::operator[](int i) const {
    return xs[i];
}

void sisd_vec4::negate() {
    for (auto & x : xs) {
        x = -x;
    }
}

void sisd_vec4::invert() {
    for (auto & x : xs) {
        x = bf(1) / x;
    }
}

void sisd_vec4::operator+=(sisd_vec4 &other) {
    for (int i = 0; i < 4; i++) {
        xs[i] += other.xs[i];
    }
}

void sisd_vec4::operator-=(sisd_vec4 &other) {
    for (int i = 0; i < 4; i++) {
        xs[i] -= other.xs[i];
    }
}

void sisd_vec4::operator*=(sisd_vec4 &other) {
    for (int i = 0; i < 4; i++) {
        xs[i] *= other.xs[i];
    }
}

void sisd_vec4::operator/=(sisd_vec4 &other) {
    for (int i = 0; i < 4; i++) {
        xs[i] /= other.xs[i];
    }
}
