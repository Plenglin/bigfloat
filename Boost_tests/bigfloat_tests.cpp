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
        BOOST_REQUIRE_CLOSE(float(bigfloat(a) * b), a * b, FLOAT_TOLERANCE); \
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

    TEST_F_ADDITION_CASE(af_mp1, -1.0f, 2.0f)
    TEST_F_ADDITION_CASE(af_mp2, -2.0f, 1.0f)
    TEST_F_ADDITION_CASE(af_pm1, 2.0f, -1.0f)
    TEST_F_ADDITION_CASE(af_pm3, -2.0f, 1.75f)
    TEST_F_ADDITION_CASE(af8, -0.2f, -0.9f)

    TEST_F_SUBTRACTION_CASE(sf1, 0.25f, 0.5f)
    TEST_F_SUBTRACTION_CASE(sf2, 0.625f, 0.375f)
    TEST_F_SUBTRACTION_CASE(sf3, 0.8f, 0.6f)
    TEST_F_SUBTRACTION_CASE(sf4, 0.937498723478932789425f, 0.91267467283412345f)
    TEST_F_SUBTRACTION_CASE(sf5, 9e-2f, 1.23e4f)

    TEST_F_SUBTRACTION_CASE(sf_mp1, -1.0f, 2.0f)
    TEST_F_SUBTRACTION_CASE(sf_mp2, -2.0f, 1.0f)
    TEST_F_SUBTRACTION_CASE(sf_pm1, 2.0f, -1.0f)
    TEST_F_SUBTRACTION_CASE(sf_pm3, -2.0f, 1.75f)
    TEST_F_SUBTRACTION_CASE(sf8, -0.2f, -0.9f)

    TEST_F_MULTIPLICATION_CASE(mf1, 1321.0f, 3)
    TEST_F_MULTIPLICATION_CASE(mf2, 234.3f, -2341)
    TEST_F_MULTIPLICATION_CASE(mf3, 2434.0f, 0)
    TEST_F_MULTIPLICATION_CASE(mf4, 0.1323f, 27398)
    TEST_F_MULTIPLICATION_CASE(mf5, 2332e-5f, 3)
BOOST_AUTO_TEST_SUITE_END();


#pragma clang diagnostic pop