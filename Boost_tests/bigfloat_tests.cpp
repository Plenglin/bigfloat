#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"
#pragma ide diagnostic ignored "cert-err58-cpp"
//
// Created by astrid on 8/18/20.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include "../bigfloat.hpp"
#include <limits>


using namespace std;


BOOST_AUTO_TEST_SUITE(bigfloat_test_suite)

    BOOST_AUTO_TEST_CASE(construct_with_double) {
        BOOST_REQUIRE_EQUAL(bigfloat(0.5), bigfloat(0, 126, 0));
        BOOST_REQUIRE_EQUAL(bigfloat(128.0), bigfloat(0, 134, 0));
    }

    BOOST_AUTO_TEST_CASE(construct_with_float) {
        // https://www.h-schmidt.net/FloatConverter/IEEE754.html this is useful for test generation

        BOOST_REQUIRE_EQUAL(bigfloat(0.5f), bigfloat(0, 126, 0));
        BOOST_REQUIRE_EQUAL(bigfloat(0.1f), bigfloat(0, 123, 5033165l << 40));
        BOOST_REQUIRE_EQUAL(bigfloat(128.0f), bigfloat(0, 134, 0));
        BOOST_REQUIRE_EQUAL(bigfloat(-0.1f), bigfloat(1, 123, 5033165l << 40));
        BOOST_REQUIRE_EQUAL(bigfloat(numeric_limits<float>::infinity()), bigfloat(0, 255, 0));
        BOOST_REQUIRE_EQUAL(bigfloat(-numeric_limits<float>::infinity()), bigfloat(1, 255, 0));
    }

    BOOST_AUTO_TEST_CASE(convert_to_float) {
        // https://www.h-schmidt.net/FloatConverter/IEEE754.html this is useful for test generation

        BOOST_REQUIRE_EQUAL(float(bigfloat(0.5f)), 0.5f);
        BOOST_REQUIRE_EQUAL(float(bigfloat(0.324578f)), 0.324578f);
        BOOST_REQUIRE_EQUAL(float(bigfloat(9.923478e8f)), 9.923478e8f);
    }

    BOOST_AUTO_TEST_CASE(addition) {
        bigfloat a = 0.3f;
        bigfloat b = 0.15f;
        BOOST_REQUIRE_EQUAL(float(a + b), 0.3f + 0.15f);
    }

BOOST_AUTO_TEST_SUITE_END()

#pragma clang diagnostic pop