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


#define FLOAT_TOLERANCE 0.0001
#define DOUBLE_TOLERANCE 0.0001

#define TEST_F_ADDITION_CASE(name, a, b) \
    BOOST_AUTO_TEST_CASE(name) { \
        BOOST_REQUIRE_CLOSE(float(bigfloat(a) + bigfloat(b)), a + b, FLOAT_TOLERANCE); \
    }

#define TEST_F_SUBTRACTION_CASE(name, a, b) \
    BOOST_AUTO_TEST_CASE(name) { \
        BOOST_REQUIRE_CLOSE(float(bigfloat(a) - bigfloat(b)), a - b, FLOAT_TOLERANCE); \
    }

#define TEST_F_MULTIPLICATION_CASE(name, a, b) \
    BOOST_AUTO_TEST_CASE(name) { \
        BOOST_REQUIRE_CLOSE(float(bigfloat(a) * bigfloat(b)), a * b, FLOAT_TOLERANCE); \
    }

#define TEST_F_DIVISION_CASE(name, a, b) \
    BOOST_AUTO_TEST_CASE(name) { \
        BOOST_REQUIRE_CLOSE(float(bigfloat(a) / bigfloat(b)), a / b, FLOAT_TOLERANCE); \
    }

#define TEST_CONVERSION_CASE(name, type, x) BOOST_AUTO_TEST_CASE(name) { BOOST_REQUIRE_EQUAL(type(bigfloat(x)), x); }


using namespace std;



BOOST_AUTO_TEST_SUITE(bigfloat_conversion)
    TEST_CONVERSION_CASE(dbd1, double, 0.5);
    TEST_CONVERSION_CASE(dbd2, double, 0.324578);
    TEST_CONVERSION_CASE(dbd3, double, 9.923478e8);

    TEST_CONVERSION_CASE(fbf1, float, 0.5f);
    TEST_CONVERSION_CASE(fbf2, float, 0.324578f);
    TEST_CONVERSION_CASE(fbf3, float, 9.923478e8f);

    BOOST_AUTO_TEST_CASE(fb_construct_special) {
        BOOST_REQUIRE_EQUAL(bigfloat(numeric_limits<float>::infinity()), bigfloat(0, 255, 0));
        BOOST_REQUIRE_EQUAL(bigfloat(-numeric_limits<float>::infinity()), bigfloat(1, 255, 0));
    }
BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(bigfloat_operands)
    TEST_F_ADDITION_CASE(af1, 0.25f, 0.5f)
    TEST_F_ADDITION_CASE(af2, 0.625f, 0.375f)
    TEST_F_ADDITION_CASE(af3, 0.8f, 0.6f)
    TEST_F_ADDITION_CASE(af4, 0.937498723478932789425f, 0.91267467283412345f)
    TEST_F_ADDITION_CASE(af5, 9e-2f, 1.23e4f)

    TEST_F_ADDITION_CASE(af6, -0.8f, 0.9f)
    TEST_F_ADDITION_CASE(af7, 2.0f, -1.0f)
    TEST_F_ADDITION_CASE(af8, -0.2f, -0.9f)
BOOST_AUTO_TEST_SUITE_END();


#pragma clang diagnostic pop