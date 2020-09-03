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


#define TEST_ADDITION_CASE(type, a, b) BOOST_REQUIRE_EQUAL(type(bigfloat(a) + bigfloat(b)), a + b);
#define TEST_CONVERSION_CASE(type, x) BOOST_REQUIRE_EQUAL(type(bigfloat(x)), x);


using namespace std;


BOOST_AUTO_TEST_SUITE(bigfloat_test_suite)

    BOOST_AUTO_TEST_CASE(convert_between_double) {
        TEST_CONVERSION_CASE(double, 0.5);
        TEST_CONVERSION_CASE(double, 0.324578);
        TEST_CONVERSION_CASE(double, 9.923478e8);
    }

    BOOST_AUTO_TEST_CASE(convert_between_float) {
        TEST_CONVERSION_CASE(float, 0.5f);
        TEST_CONVERSION_CASE(float, 0.324578f);
        TEST_CONVERSION_CASE(float, 9.923478e8f);
    }

    BOOST_AUTO_TEST_CASE(float_construct_special) {
        BOOST_REQUIRE_EQUAL(bigfloat(numeric_limits<float>::infinity()), bigfloat(0, 255, 0));
        BOOST_REQUIRE_EQUAL(bigfloat(-numeric_limits<float>::infinity()), bigfloat(1, 255, 0));
    }

    BOOST_AUTO_TEST_CASE(simple_float_addition) {
        TEST_ADDITION_CASE(float, 0.25f, 0.5f)
        //TEST_ADDITION_CASE(float, 0.8, 0.6)
        //TEST_ADDITION_CASE(float, 0.937498723478932789425f, 0.91267467283412345f)
    }

BOOST_AUTO_TEST_SUITE_END()

#pragma clang diagnostic pop