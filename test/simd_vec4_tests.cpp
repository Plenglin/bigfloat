#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <iostream>
#include "_include.hpp"
#include "../bf.hpp"
#include "../simd_vec4.hpp"


using namespace bigfloat;
using namespace bigfloat::simd;

BOOST_AUTO_TEST_SUITE(bigfloat_simd_vec4)
    // Test cases, preferably non-zero/nan/inf ones. The zero ones can get their own test cases.
    static const auto DATA =
              data::make(ARR1) ^ data::make(ARR2) ^ data::make(ARR1) ^ data::make(ARR2)
            ^ data::make(ARR2) ^ data::make(ARR1) ^ data::make(ARR2) ^ data::make(ARR1);

    BOOST_DATA_TEST_CASE(preserves_bf, DATA, x0, x1, x2, x3, _0, _1, _2, _3) {
        auto bx0 = bf(x0);
        auto bx1 = bf(x1);
        auto bx2 = bf(x2);
        auto bx3 = bf(x3);
        auto as = simd_vec4(bx0, bx1, bx2, bx3);

        BOOST_REQUIRE_EQUAL(as[0], bx0);
        BOOST_REQUIRE_EQUAL(as[1], bx1);
        BOOST_REQUIRE_EQUAL(as[2], bx2);
        BOOST_REQUIRE_EQUAL(as[3], bx3);
    }

    /*
    BOOST_DATA_TEST_CASE(vec4_mul_is_correct, DATA, x0, x1, x2, x3, x4, x5, x6, x7) {
        auto bx0 = bf(x0);
        auto bx1 = bf(x1);
        auto bx2 = bf(x2);
        auto bx3 = bf(x3);
        auto bx4 = bf(x4);
        auto bx5 = bf(x5);
        auto bx6 = bf(x6);
        auto bx7 = bf(x7);

        simd_vec4 as = simd_vec4(bx0, bx1, bx2, bx3);
        simd_vec4 bs = simd_vec4(bx4, bx5, bx6, bx7);

        as *= bs;

        BOOST_REQUIRE_CLOSE(as[0], bx0 * bx4, DOUBLE_TOLERANCE);
        BOOST_REQUIRE_CLOSE(as[1], bx1 * bx5, DOUBLE_TOLERANCE);
        BOOST_REQUIRE_CLOSE(as[2], bx2 * bx6, DOUBLE_TOLERANCE);
        BOOST_REQUIRE_CLOSE(as[3], bx3 * bx7, DOUBLE_TOLERANCE);
    }*/

BOOST_AUTO_TEST_SUITE_END();
#pragma clang diagnostic pop