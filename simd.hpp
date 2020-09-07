#ifndef BIGFLOAT_SIMD_HPP
#define BIGFLOAT_SIMD_HPP

#include "bf.hpp"

namespace bigfloat::simd {
    // Adds a 2-vector of bigfloats together and writes into the first vector.
    void add_2(bf a[2], bf b[2]);
    void sub_2(bf a[2], bf b[2]);
    void mul_2(bf a[2], bf b[2]);
    void div_2(bf a[2], bf b[2]);

    void add_4(bf a[4], bf b[4]);
    void sub_4(bf a[4], bf b[4]);
    void mul_4(bf a[4], bf b[4]);
    void div_4(bf a[4], bf b[4]);

    void add_8(bf a[8], bf b[8]);
    void sub_8(bf a[8], bf b[8]);
    void mul_8(bf a[8], bf b[8]);
    void div_8(bf a[8], bf b[8]);

    void add_n(bf a[8], bf b[8]);
    void sub_n(bf a[8], bf b[8]);
    void mul_n(bf a[8], bf b[8]);
    void div_n(bf a[8], bf b[8]);
}

#endif //BIGFLOAT_SIMD_HPP
