#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <iostream>
#include "_include.hpp"
#include "../bf.hpp"
#include "../simd_vec2.hpp"


using namespace bigfloat;
using namespace bigfloat::simd;

BOOST_AUTO_TEST_SUITE(bigfloat_simd)
    // Test cases, preferably non-zero/nan/inf ones. The zero ones can get their own test cases.
    static const auto DATA =
            data::make({
                               1.0,
                               1.0,
                               0.25,
                               0.625,
                               0.8,
                               0.937498723478932789425,
                               9e-2,
                               -1.,
                               -2.,
                               2.0,
                               -2.,
                               1.0,
                               1.0,
                               1321.0,
                               234.3,
                               0.1323,
                               2332e-5
                       }) ^
            data::make({
                               2.0,
                               0.5,
                               0.375,
                               0.6,
                               0.91267467283412345,
                               1.23e4,
                               2.0,
                               1.0,
                               -1.0,
                               1.75,
                               -0.9,
                               2.0,
                               3.0,
                               3.34,
                               -234.123,
                               2739.8,
                               3.32
                       }) ^
            data::make({
                               2.0,
                               3.0,
                               0.5,
                               0.375,
                               0.91267467283412345,
                               1.23e4,
                               2.0,
                               1.0,
                               -1.0,
                               1.75,
                               -0.9,
                               2.0,
                               3.0,
                               3.34,
                               -234.123,
                               2739.8,
                               3.32
                       }) ^
            data::make({
                               2.0,
                               3.0,
                               0.5,
                               0.91267467283412345,
                               1.23e4,
                               2.0,
                               1.0,
                               -1.0,
                               1.75,
                               -0.9,
                               2.0,
                               0.6,
                               3.0,
                               3.34,
                               -234.123,
                               2739.8,
                               3.32
                       });

    BOOST_DATA_TEST_CASE(vec2_preserves_bf, DATA, x0, x1, _a, _b) {
        auto bx0 = bf(x0);
        auto bx1 = bf(x1);
        auto as = vec2(bx0, bx1);

        BOOST_REQUIRE_EQUAL(as[0], bx0);
        BOOST_REQUIRE_EQUAL(as[1], bx1);
    }

    BOOST_DATA_TEST_CASE(mul_2_is_correct, DATA, x0, x1, x2, x3) {
        vec2 as = vec2(bf(x0), bf(x1));
        vec2 bs = vec2(bf(x2), bf(x3));
        bf expected[2] = {as[0] * as[1], bs[0] * bs[1]};

        as *= bs;

        BOOST_REQUIRE_EQUAL(as[0], expected[0]);
        BOOST_REQUIRE_EQUAL(as[1], expected[1]);
    }

BOOST_AUTO_TEST_SUITE_END();
#pragma clang diagnostic pop