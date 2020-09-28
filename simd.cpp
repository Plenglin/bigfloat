//
// Created by astrid on 9/27/20.
//

#include "simd.hpp"

using namespace bigfloat::simd;
/*
vecn::vecn(const std::vector<bf>& xs) : vecs(xs.size() / 4) {
    for (int i = 0; i < xs.size();) {
        bf x0 = xs[i++];
        bf x1 = xs[i++];
        bf x2 = xs[i++];
        bf x3 = xs[i++];
        vecs[i] = vec4(x0, x1, x2, x3);
    }
}

bigfloat::bf vecn::operator[](int i) const {
    return vecs[i / 4][i & 0x3];
}

void vecn::invert() {
    for (auto &x : vecs) {
        x.invert();
    }
}

void vecn::negate() {
    for (auto &x : vecs) {
        x.negate();
    }
}

void vecn::operator+=(vecn &other) {
    for (auto i = 0; i < vecs.size(); i++) {
        vecs[i] += other.vecs[i];
    }
}

void vecn::operator-=(vecn &other) {
    for (auto i = 0; i < vecs.size(); i++) {
        vecs[i] -= other.vecs[i];
    }
}

void vecn::operator*=(vecn &other) {
    for (auto i = 0; i < vecs.size(); i++) {
        vecs[i] *= other.vecs[i];
    }
}

void vecn::operator/=(vecn &other) {
    for (auto i = 0; i < vecs.size(); i++) {
        vecs[i] /= other.vecs[i];
    }
}
*/