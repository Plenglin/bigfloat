#include "_include.hpp"

#include "avx_helper.hpp"

#define MSB 1UL << 62

using namespace std;
using namespace bigfloat::helper;
namespace data = boost::unit_test::data;
namespace mono = data::monomorphic;

BOOST_AUTO_TEST_SUITE(bigfloat_helper)
    static const auto VALUES =
            data::make({
                               (1UL << 48) | MSB,
                               8674123984219UL | MSB,
                               129813849123UL | MSB,
                               98139757813497172UL | MSB,
                               9123219UL | MSB,
                               8712376812UL | MSB,
                       }) ^
                    data::make({
                                       (1UL << 48) | MSB,
                                       8674123984219UL | MSB,
                                       129813849123UL | MSB,
                                       98139757813497172UL | MSB,
                                       9123219UL | MSB,
                                       8712376812UL | MSB,
                               }) ^
                    data::make({
                                       (1UL << 48) | MSB,
                                       8674123984219UL | MSB,
                                       129813849123UL | MSB,
                                       98139757813497172UL | MSB,
                                       9123219UL | MSB,
                                       8712376812UL | MSB,
                               }) ^
                    data::make({
                                       (1UL << 48) | MSB,
                                       8674123984219UL | MSB,
                                       129813849123UL | MSB,
                                       98139757813497172UL | MSB,
                                       9123219UL | MSB,
                                       8712376812UL | MSB,
                               })
                        ;

    BOOST_DATA_TEST_CASE(multiply_keep_upper_no_carry_is_correct, VALUES, a, b, c, d) {
        unsigned __int128 mul = (unsigned __int128)a * (unsigned __int128)b;
        unsigned long ea = multiply_keep_upper_no_carry(a, a);
        unsigned long eb = multiply_keep_upper_no_carry(b, b);
        unsigned long ec = multiply_keep_upper_no_carry(c, c);
        unsigned long ed = multiply_keep_upper_no_carry(d, d);

        __m256i v = _mm256_set_epi64x(a, b, c, d);
        __m256i p = multiply_keep_upper_no_carry(v, v);
        unsigned long *out = (unsigned long*)&p;

        BOOST_REQUIRE_GE(ea, out[0]);
        BOOST_REQUIRE_LE(ea - 2, out[0]);
        BOOST_REQUIRE_GE(eb, out[1]);
        BOOST_REQUIRE_LE(eb - 2, out[1]);
        BOOST_REQUIRE_GE(ec, out[2]);
        BOOST_REQUIRE_LE(ec - 2, out[2]);
        BOOST_REQUIRE_GE(ed, out[3]);
        BOOST_REQUIRE_LE(ed - 2, out[3]);
    }
BOOST_AUTO_TEST_SUITE_END();