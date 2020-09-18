#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"
#pragma ide diagnostic ignored "cert-err58-cpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN

#include "_include.hpp"

using namespace std;
using namespace bigfloat;
namespace data = boost::unit_test::data;
namespace mono = data::monomorphic;

BOOST_AUTO_TEST_SUITE(bigfloat_conversion)
    static const auto VALUES =
        data::make({
                           0.5,
                           0.324578,
                           9.923478e8,
                           9.71234971627894,
                           -81.3426678123,
                           0.0
        });

    BOOST_DATA_TEST_CASE(double_to_bf_to_double_preserves_value, VALUES, x) {
        BOOST_REQUIRE_EQUAL(double(bf(x)), x);
    }

    BOOST_AUTO_TEST_CASE(db_construct_special) {
        // TODO write this
        // BOOST_REQUIRE_EQUAL(bf(numeric_limits<double>::infinity()), bf(0, 255, 0));
        // BOOST_REQUIRE_EQUAL(bf(-numeric_limits<double>::infinity()), bf(1, 255, 0));
    }
BOOST_AUTO_TEST_SUITE_END();

    /*
BOOST_AUTO_TEST_SUITE(bigfloat_to_str)
    BOOST_AUTO_TEST_CASE(name) { \
        std::stringstream os1; \
        os1 << bf(x); \
        std::stringstream os2; \
        os2 << x; \
        BOOST_REQUIRE_EQUAL(os1.str(), os2.str()); \
    }
BOOST_AUTO_TEST_SUITE_END();*/

// Test cases, preferably non-zero/nan/inf ones. The zero ones can get their own test cases.
static const auto PAIRS = data::make(ARR1) ^ data::make(ARR2);

BOOST_AUTO_TEST_SUITE(bigfloat_ops)
    BOOST_DATA_TEST_CASE(add, PAIRS, a, b) {
        BOOST_REQUIRE_CLOSE(double(bf(a) + bf(b)), a + b, DOUBLE_TOLERANCE);
    }
    BOOST_DATA_TEST_CASE(sub, PAIRS, a, b) {
        BOOST_REQUIRE_CLOSE(double(bf(a) - bf(b)), a - b, DOUBLE_TOLERANCE);
    }

    BOOST_DATA_TEST_CASE(mul, PAIRS, a, b) {
        BOOST_REQUIRE_CLOSE(double(bf(a) * bf(b)), a * b, DOUBLE_TOLERANCE);
    }
    BOOST_AUTO_TEST_CASE(mul_x_zero_is_zero) {
        BOOST_REQUIRE_EQUAL(double(bf(32.13) * bf(0)), 0.0);
    }

    BOOST_DATA_TEST_CASE(div, PAIRS, a, b) {
        BOOST_REQUIRE_CLOSE(double(bf(a) / bf(b)), a / b, DOUBLE_TOLERANCE);
    }
    BOOST_AUTO_TEST_CASE(div_x_zero_is_p_inf) {
        BOOST_REQUIRE((bf(2349.23) / bf(0)).is_inf());
    }
    BOOST_AUTO_TEST_CASE(div_zero_x_is_zero) {
        BOOST_REQUIRE_EQUAL(double(bf(0) / bf(2349.23)), 0.0 / 2349.23);
    }
    BOOST_AUTO_TEST_CASE(div_zero_zero_is_nan) {
        BOOST_REQUIRE(std::isnan(double(bf(0) / bf(0))));
    }
BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(bigfloat_cmp)
    BOOST_DATA_TEST_CASE(lt, PAIRS, a, b) {
        BOOST_REQUIRE_EQUAL(double(bf(a) < bf(b)), a < b);
    }
    BOOST_DATA_TEST_CASE(lte, PAIRS, a, b) {
        BOOST_REQUIRE_EQUAL(double(bf(a) <= bf(b)), a <= b);
    }
    BOOST_DATA_TEST_CASE(gt, PAIRS, a, b) {
        BOOST_REQUIRE_EQUAL(double(bf(a) > bf(b)), a > b);
    }
    BOOST_DATA_TEST_CASE(gte, PAIRS, a, b) {
        BOOST_REQUIRE_EQUAL(double(bf(a) >= bf(b)), a >= b);
    }
BOOST_AUTO_TEST_SUITE_END();

#pragma clang diagnostic pop