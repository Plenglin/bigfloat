//
// Created by astrid on 8/18/20.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include "../bigfloat.h"
#include <math.h>


void require_bf_eq(bigfloat bf, bool sign, unsigned char exponent, unsigned long mantissa) {
    BOOST_REQUIRE_EQUAL(bf.sign, sign);
    BOOST_REQUIRE_EQUAL(bf.mantissa, mantissa);
    BOOST_REQUIRE_EQUAL(bf.exponent, exponent);
}

void require_bf_eq(bigfloat bf, bigfloat bf2) {
    BOOST_REQUIRE_EQUAL(bf.sign, bf2.sign);
    BOOST_REQUIRE_EQUAL(bf.mantissa, bf2.mantissa);
    BOOST_REQUIRE_EQUAL(bf.exponent, bf2.exponent);
}


BOOST_AUTO_TEST_SUITE(bigfloat_test_suite)

    BOOST_AUTO_TEST_CASE(construct_with_double) {
    }

    BOOST_AUTO_TEST_CASE(construct_with_float) {
        require_bf_eq(bigfloat(0.5f), 0, 126, 0);

    }

BOOST_AUTO_TEST_SUITE_END()
