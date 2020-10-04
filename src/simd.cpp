//
// Created by astrid on 9/27/20.
//

#include "../include/simd.hpp"

using namespace bigfloat;
using namespace bigfloat::simd;


vecn::vecn(size_t count) : count(count) {
    count = (count + 3) / 4;
    mantissa = new unsigned long [count];
    exponent = new long [count];
    sign = new char [count];
}

vecn::vecn(std::vector<bf> vecs) : vecn(vecs.size()) {
    for (int i = 0; i < vecs.size(); i++) {
        bf x = vecs[i];
        exponent[i] = x.exponent;
        if (x.mantissa < 0) {
            mantissa[i] = -x.mantissa;
            sign[i] = 1;
        } else {
            mantissa[i] = x.mantissa;
            sign[i] = 0;
        }
    }
}

vecn::~vecn() {
    delete mantissa;
    delete exponent;
    delete sign;
}

bf vecn::operator[](int i) const {
    return bf(exponent[i], sign[i] ? -(long)mantissa[i] : (long)mantissa[i]);
}

vec4 vecn::get_vec(int offset) const {
    __m256i mt = _mm256_load_si256((__m256i*)mantissa);
    __m256i ex = _mm256_load_si256((__m256i*)exponent);
    int s = (sign[offset + 3] << 3) |
            (sign[offset + 2] << 2) |
            (sign[offset + 1] << 1) |
            sign[offset];
    return vec4(s, ex, mt);
}

vec4 vecn::set_vec(int offset, vec4 &v) {
    _mm256_store_pd((double*)exponent + offset, (__m256d)v.exponent);
    _mm256_store_pd((double*)mantissa + offset, (__m256d)v.mantissa);
    sign[offset] = v.sign & 1;
    sign[offset + 1] = (v.sign >> 1) & 1;
    sign[offset + 2] = (v.sign >> 2) & 1;
    sign[offset + 3] = (v.sign >> 3) & 1;
}

void vecn::invert() {
    for (int i = 0; i < count; i += 4) {
        auto v = get_vec(i);
        v.invert();
        set_vec(i, v);
    }
}

void vecn::negate() {
    for (int i = 0; i < count; i += 4) {
        sign[i] = ~sign[i];
    }
}

void vecn::operator+=(vecn &other) {
    for (int i = 0; i < count; i += 4) {
        auto a = get_vec(i);
        auto b = other.get_vec(i);
        a += b;
        set_vec(i, a);
    }
}

void vecn::operator-=(vecn &other) {
    for (int i = 0; i < count; i += 4) {
        auto a = get_vec(i);
        auto b = other.get_vec(i);
        a -= b;
        set_vec(i, a);
    }
}

void vecn::operator*=(vecn &other) {
    for (int i = 0; i < count; i += 4) {
        auto a = get_vec(i);
        auto b = other.get_vec(i);
        a *= b;
        set_vec(i, a);
    }
}

void vecn::operator/=(vecn &other) {
    for (int i = 0; i < count; i += 4) {
        auto a = get_vec(i);
        auto b = other.get_vec(i);
        a /= b;
        set_vec(i, a);
    }
}
