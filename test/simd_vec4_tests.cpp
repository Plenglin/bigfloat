#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <iostream>
#include <bigfloat/bf.hpp>
#include <bigfloat/simd_vec4.hpp>
#include <bigfloat/avx_helper.hpp>

#include "_include.hpp"

using namespace bigfloat;
using namespace bigfloat::helper;

BOOST_AUTO_TEST_SUITE(bigfloat_simd_vec4)
    // Test cases, preferably non-zero/nan/inf ones. The zero ones can get their own test cases.
    static const auto DATA =
            (data::make(ARR1) ^ data::make(ARR2) ^ data::make(ARR1) ^ data::make(ARR2)
            ^ data::make(ARR2) ^ data::make(ARR1) ^ data::make(ARR2) ^ data::make(ARR1));

    BOOST_DATA_TEST_CASE(preserves_bf, DATA, x0, x1, x2, x3, _0, _1, _2, _3) {
        auto bx0 = bf(x0);
        auto bx1 = bf(x1);
        auto bx2 = bf(x2);
        auto bx3 = bf(x3);

        auto as = simd_vec4(bx0, bx1, bx2, bx3);

        BOOST_REQUIRE_EQUAL(bf(as[0]), bx0);
        BOOST_REQUIRE_EQUAL(bf(as[1]), bx1);
        BOOST_REQUIRE_EQUAL(bf(as[2]), bx2);
        BOOST_REQUIRE_EQUAL(bf(as[3]), bx3);
    }

    BOOST_AUTO_TEST_CASE(converts_to_double_zeros) {
        auto bfvec = simd_vec4(1, 0, 0, 0);

        union {
            __m256d dv;
            double ds[4];
        };
        dv = __m256d(bfvec);

        BOOST_REQUIRE_EQUAL(double(ds[0]), 1.0);
        BOOST_REQUIRE_EQUAL(double(ds[1]), 0.0);
        BOOST_REQUIRE_EQUAL(double(ds[2]), 0.0);
        BOOST_REQUIRE_EQUAL(double(ds[3]), 0.0);
    }

    BOOST_DATA_TEST_CASE(converts_to_double, DATA, x0, x1, x2, x3, _0, _1, _2, _3) {
        auto bx0 = bf(x0);
        auto bx1 = bf(x1);
        auto bx2 = bf(x2);
        auto bx3 = bf(x3);
        auto bfvec = simd_vec4(bx0, bx1, bx2, bx3);

        union {
            __m256d dv;
            double ds[4];
        };
        dv = __m256d(bfvec);

        BOOST_REQUIRE_EQUAL(bf(ds[0]), double(bx0));
        BOOST_REQUIRE_EQUAL(bf(ds[1]), double(bx1));
        BOOST_REQUIRE_EQUAL(bf(ds[2]), double(bx2));
        BOOST_REQUIRE_EQUAL(bf(ds[3]), double(bx3));
    }

    BOOST_DATA_TEST_CASE(converts_from_double, DATA, x0, x1, x2, x3, _0, _1, _2, _3) {
        auto bx0 = bf(x0);
        auto bx1 = bf(x1);
        auto bx2 = bf(x2);
        auto bx3 = bf(x3);
        auto bfvec = simd_vec4(bx0, bx1, bx2, bx3);

        auto as = simd_vec4(__m256d(bfvec));

        BOOST_REQUIRE_EQUAL(bf(as[0]), bf(double(bx0)));
        BOOST_REQUIRE_EQUAL(bf(as[1]), bf(double(bx1)));
        BOOST_REQUIRE_EQUAL(bf(as[2]), bf(double(bx2)));
        BOOST_REQUIRE_EQUAL(bf(as[3]), bf(double(bx3)));
    }

    BOOST_DATA_TEST_CASE(vec4_add_is_correct, DATA, x0, x1, x2, x3, x4, x5, x6, x7) {
        auto bx0 = bf(x0);
        auto bx1 = bf(x1);
        auto bx2 = bf(x2);
        auto bx3 = bf(x3);
        auto bx4 = bf(x4);
        auto bx5 = bf(x5);
        auto bx6 = bf(x6);
        auto bx7 = bf(x7);
        auto e0 = bx0 + bx4;
        auto e1 = bx1 + bx5;
        auto e2 = bx2 + bx6;
        auto e3 = bx3 + bx7;

        simd_vec4 as = simd_vec4(bx0, bx1, bx2, bx3);
        simd_vec4 bs = simd_vec4(bx4, bx5, bx6, bx7);

        as += bs;

        bf a0 = as[0];
        bf a1 = as[1];
        bf a2 = as[2];
        bf a3 = as[3];
        BOOST_REQUIRE_EQUAL(a0, e0);
        BOOST_REQUIRE_EQUAL(a1, e1);
        BOOST_REQUIRE_EQUAL(a2, e2);
        BOOST_REQUIRE_EQUAL(a3, e3);
    }

    BOOST_DATA_TEST_CASE(vec4_sub_is_correct, DATA, x0, x1, x2, x3, x4, x5, x6, x7) {
        auto bx0 = bf(x0);
        auto bx1 = bf(x1);
        auto bx2 = bf(x2);
        auto bx3 = bf(x3);
        auto bx4 = bf(x4);
        auto bx5 = bf(x5);
        auto bx6 = bf(x6);
        auto bx7 = bf(x7);
        auto e0 = bx0 - bx4;
        auto e1 = bx1 - bx5;
        auto e2 = bx2 - bx6;
        auto e3 = bx3 - bx7;

        simd_vec4 as = simd_vec4(bx0, bx1, bx2, bx3);
        simd_vec4 bs = simd_vec4(bx4, bx5, bx6, bx7);

        as -= bs;

        bf a0 = as[0];
        bf a1 = as[1];
        bf a2 = as[2];
        bf a3 = as[3];
        BOOST_REQUIRE_CLOSE(a0, e0, bf(1e-9));
        BOOST_REQUIRE_CLOSE(a1, e1, bf(1e-9));
        BOOST_REQUIRE_CLOSE(a2, e2, bf(1e-9));
        BOOST_REQUIRE_CLOSE(a3, e3, bf(1e-9));
    }

    BOOST_DATA_TEST_CASE(vec4_mul_is_correct, DATA, x0, x1, x2, x3, x4, x5, x6, x7) {
        auto bx0 = bf(x0);
        auto bx1 = bf(x1);
        auto bx2 = bf(x2);
        auto bx3 = bf(x3);
        auto bx4 = bf(x4);
        auto bx5 = bf(x5);
        auto bx6 = bf(x6);
        auto bx7 = bf(x7);
        auto e0 = bx0 * bx4;
        auto e1 = bx1 * bx5;
        auto e2 = bx2 * bx6;
        auto e3 = bx3 * bx7;

        simd_vec4 as = simd_vec4(bx0, bx1, bx2, bx3);
        simd_vec4 bs = simd_vec4(bx4, bx5, bx6, bx7);

        as *= bs;

        bf a0 = as[0];
        bf a1 = as[1];
        bf a2 = as[2];
        bf a3 = as[3];
        BOOST_REQUIRE_EQUAL(a0, e0);
        BOOST_REQUIRE_EQUAL(a1, e1);
        BOOST_REQUIRE_EQUAL(a2, e2);
        BOOST_REQUIRE_EQUAL(a3, e3);
    }

    BOOST_DATA_TEST_CASE(vec4_div_is_correct, DATA, x0, x1, x2, x3, x4, x5, x6, x7) {
        auto bx0 = bf(x0);
        auto bx1 = bf(x1);
        auto bx2 = bf(x2);
        auto bx3 = bf(x3);
        auto bx4 = bf(x4);
        auto bx5 = bf(x5);
        auto bx6 = bf(x6);
        auto bx7 = bf(x7);
        auto e0 = bx0 / bx4;
        auto e1 = bx1 / bx5;
        auto e2 = bx2 / bx6;
        auto e3 = bx3 / bx7;

        simd_vec4 as = simd_vec4(bx0, bx1, bx2, bx3);
        simd_vec4 bs = simd_vec4(bx4, bx5, bx6, bx7);

        as /= bs;

        bf a0 = as[0];
        bf a1 = as[1];
        bf a2 = as[2];
        bf a3 = as[3];
        BOOST_REQUIRE_EQUAL(a0, e0);
        BOOST_REQUIRE_EQUAL(a1, e1);
        BOOST_REQUIRE_EQUAL(a2, e2);
        BOOST_REQUIRE_EQUAL(a3, e3);
    }

    BOOST_AUTO_TEST_CASE(to_string) {
        simd_vec4 v = simd_vec4(1, 0, 0, 0.02);
        bf b = bf(0.02);

        stringstream ssb;
        ssb << b;

        stringstream ssc;
        ssc << bf(v[3]);

        stringstream ssv;
        ssv << v;

        std::cout << int(2) << endl;

        BOOST_REQUIRE_EQUAL("0.02", ssb.str());
        BOOST_REQUIRE_EQUAL(bf(0.02), bf(v[3]));
        BOOST_REQUIRE_EQUAL(b, bf(v[3]));
        BOOST_REQUIRE_EQUAL("0.02", ssc.str());
        BOOST_REQUIRE_EQUAL("[1,0,0,0.02]", ssv.str());
    }

BOOST_AUTO_TEST_SUITE_END();
#pragma clang diagnostic pop