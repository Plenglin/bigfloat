#include "_include.hpp"

#include "../avx_helper.hpp"

using namespace std;
using namespace bigfloat::helper;
namespace data = boost::unit_test::data;
namespace mono = data::monomorphic;

BOOST_AUTO_TEST_SUITE(bigfloat_helper)
    static const auto VALUES =
            data::make({
                                1UL << 48,
                                (1UL << 48) + (1UL << 16),
                                8674123984219UL,
                                129813849123UL,
                                981397578134971782UL,
                                9123219UL,
                                8712376812UL,
                        }) ^
            data::make({
                                1UL << 48,
                                (1UL << 48) + (1UL << 16),
                                8674123919UL,
                                1298138491234231423UL,
                                981397134971782UL,
                                9123212234239UL,
                                871237432236812UL,
                        });

    BOOST_DATA_TEST_CASE(multiply_keep_upper_no_carry_is_correct, VALUES, a, b) {
        unsigned __int128 mul = (unsigned __int128)a * (unsigned __int128)b;
        unsigned long expected = mul >> 64;
        unsigned long actual = multiply_keep_upper_no_carry(a, b);
        BOOST_REQUIRE_GE(expected, actual);
        BOOST_REQUIRE_LE(expected - 1, actual);
    }
BOOST_AUTO_TEST_SUITE_END();