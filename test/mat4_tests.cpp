//
// Created by astrid on 10/18/20.
//

#include "_include.hpp"
#include <bigfloat/mat4.hpp>

using namespace bigfloat;


BOOST_AUTO_TEST_SUITE(bigfloat_mat4)
    BOOST_AUTO_TEST_CASE(identity_times_identity) {
        mat4 i1(1);
        mat4 i2(1);

        mat4 a = i1 * i2;
        BOOST_REQUIRE_EQUAL(bf(a[0][0]), bf(1));
    }

    BOOST_AUTO_TEST_CASE(conversion) {
        mat4 m1(1,0,0,0.979999,
               0,1,0,0,
               0,0,1,-3,
               0,0,0,1);
        mat4 m2(1,0,0,1,
               0,1,0,0,
               0,0,1,-3,
               0,0,0,1);

        float tx1 = float(bf(m1[0][3]));
        float tx2 = float(bf(m2[0][3]));

        BOOST_REQUIRE_EQUAL(tx1, 0.979999f);
        BOOST_REQUIRE_EQUAL(tx2, 1.0f);
    }
BOOST_AUTO_TEST_SUITE_END();

