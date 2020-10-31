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
        BOOST_REQUIRE_EQUAL(a[0][0], bf(1));
    }
BOOST_AUTO_TEST_SUITE_END();

