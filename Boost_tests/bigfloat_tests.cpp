//
// Created by astrid on 8/18/20.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include "../bigfloat.h"
#include <math.h>

BOOST_AUTO_TEST_SUITE(bigfloat_test_suite)

    BOOST_AUTO_TEST_CASE(construct_with_double) {
        float f = 0.5;
        bigfloat bf(f);

        BOOST_REQUIRE_EQUAL(bf.sign, 0);
        BOOST_REQUIRE_EQUAL(bf.mantissa, 0);
        BOOST_REQUIRE_EQUAL(bf.exponent, 0x3f00);
    }

    BOOST_AUTO_TEST_CASE(construct_with_float) {
    }

BOOST_AUTO_TEST_SUITE_END()
