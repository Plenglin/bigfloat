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
#include <cmath>


#define FLOAT_TOLERANCE 1e-4
#define DOUBLE_TOLERANCE 1e-8

#define TEST_D_ADDITION_CASE(name, a, b) \
    BOOST_AUTO_TEST_CASE(name) { \
        BOOST_REQUIRE_CLOSE(double(bigfloat(a) + bigfloat(b)), a + b, FLOAT_TOLERANCE); \
    }

#define TEST_D_SUBTRACTION_CASE(name, a, b) \
    BOOST_AUTO_TEST_CASE(name) { \
        BOOST_REQUIRE_CLOSE(double(bigfloat(a) - bigfloat(b)), a - b, FLOAT_TOLERANCE); \
    }

#define TEST_D_MULTIPLICATION_CASE(name, a, b) \
    BOOST_AUTO_TEST_CASE(name) { \
        BOOST_REQUIRE_CLOSE(double(bigfloat(a) * bigfloat(b)), a * b, FLOAT_TOLERANCE); \
    }

#define TEST_D_DIVISION_CASE(name, a, b) \
    BOOST_AUTO_TEST_CASE(name) { \
        BOOST_REQUIRE_CLOSE(double(bigfloat(a) / bigfloat(b)), a / b, FLOAT_TOLERANCE); \
    }

#define TEST_D_CONVERSION_CASE(name, x) BOOST_AUTO_TEST_CASE(name) { BOOST_REQUIRE_EQUAL(double(bigfloat(x)), x); }


using namespace std;


BOOST_AUTO_TEST_SUITE(bigfloat_conversion)
    TEST_D_CONVERSION_CASE(dbd1, 0.5);
    TEST_D_CONVERSION_CASE(dbd2, 0.324578);
    TEST_D_CONVERSION_CASE(dbd3, 9.923478e8);
    TEST_D_CONVERSION_CASE(dbd4, 9.71234971627894);
    TEST_D_CONVERSION_CASE(dbd5, -813426678123);
    TEST_D_CONVERSION_CASE(dbd6, 0.0);

    BOOST_AUTO_TEST_CASE(db_construct_special) {
        // TODO write this
        // BOOST_REQUIRE_EQUAL(bigfloat(numeric_limits<double>::infinity()), bigfloat(0, 255, 0));
        // BOOST_REQUIRE_EQUAL(bigfloat(-numeric_limits<double>::infinity()), bigfloat(1, 255, 0));
    }
BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(bigfloat_add_sub)
    TEST_D_ADDITION_CASE(a1, 0.25, 0.5)
    TEST_D_ADDITION_CASE(a2, 0.625, 0.375)
    TEST_D_ADDITION_CASE(a3, 0.8, 0.6)
    TEST_D_ADDITION_CASE(a4, 0.937498723478932789425, 0.91267467283412345)
    TEST_D_ADDITION_CASE(a5, 9e-2, 1.23e4)
    TEST_D_ADDITION_CASE(a_mp1, -1.f, 2.0)
    TEST_D_ADDITION_CASE(a_mp2, -2.f, 1.0)
    TEST_D_ADDITION_CASE(a_pm1, 2.0, -1.0)
    TEST_D_ADDITION_CASE(a_pm3, -2.f, 1.75)
    TEST_D_ADDITION_CASE(a8, -0.f, -0.9)

    TEST_D_SUBTRACTION_CASE(s1, 0.25, 0.5)
    TEST_D_SUBTRACTION_CASE(s2, 0.625, 0.375)
    TEST_D_SUBTRACTION_CASE(s3, 0.8, 0.6)
    TEST_D_SUBTRACTION_CASE(s4, 0.937498723478932789425, 0.91267467283412345)
    TEST_D_SUBTRACTION_CASE(s5, 9e-2, 1.23e4)
    TEST_D_SUBTRACTION_CASE(s_mp1, -1.0, 2.0)
    TEST_D_SUBTRACTION_CASE(s_mp2, -2.0, 1.0)
    TEST_D_SUBTRACTION_CASE(s_pm1, 2.0, -1.0)
    TEST_D_SUBTRACTION_CASE(s_pm3, -2.0, 1.75)
    TEST_D_SUBTRACTION_CASE(s8, -0.2, -0.9)
BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(bigfloat_mul)
    TEST_D_MULTIPLICATION_CASE(mbb0, 1.0, 2.0)
    TEST_D_MULTIPLICATION_CASE(mbb1, 1.0, 3.0)
    TEST_D_MULTIPLICATION_CASE(mbb2, 1321.0, 3.34)
    TEST_D_MULTIPLICATION_CASE(mbb3, 234.3, -234.123)
    TEST_D_MULTIPLICATION_CASE(mbb4, 2434.0, 0.0)
    TEST_D_MULTIPLICATION_CASE(mbb5, 0.1323, 2739.8)
    TEST_D_MULTIPLICATION_CASE(mbb6, 2332e-5, 3.32)
BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(bigfloat_div)
    TEST_D_DIVISION_CASE(dbb0, 1.0, 2.0)
    TEST_D_DIVISION_CASE(dbb1, 1.0, 3.0)
    TEST_D_DIVISION_CASE(dbb2, 1321.0, 3.34)
    TEST_D_DIVISION_CASE(dbb3, 234.3, -234.123)
    TEST_D_DIVISION_CASE(dbb5, 0.1323, 2739.8)
    TEST_D_DIVISION_CASE(dbb6, 2332e-5, 3.32)

    BOOST_AUTO_TEST_CASE(dbz) {
        BOOST_REQUIRE_EQUAL(double(bigfloat(2349.23) / bigfloat(0)), 2349.23 / 0.0);
    }
    BOOST_AUTO_TEST_CASE(dzb) {
        BOOST_REQUIRE_EQUAL(double(bigfloat(0) / bigfloat(2349.23)), 0.0 / 2349.23);
    }
    BOOST_AUTO_TEST_CASE(dzz) {
        BOOST_REQUIRE(std::isnan(double(bigfloat(0) / bigfloat(0))));
    }
BOOST_AUTO_TEST_SUITE_END();

#pragma clang diagnostic pop