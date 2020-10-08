#ifndef BIGFLOAT__INCLUDE_HPP
#define BIGFLOAT__INCLUDE_HPP

#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
#include <boost/compressed_pair.hpp>
#include "bigfloat.hpp"
#include "interop/boost.hpp"

using namespace std;
using namespace bigfloat;
namespace data = boost::unit_test::data;
namespace mono = data::monomorphic;

#define DOUBLE_TOLERANCE 1e-10

static const double ARR1[] = {
        1.0,
        -1.0,
        1.0,
        1.0,
        0.25,
        0.625,
        0.8,
        0.937498723478932789425,
        9e-2,
        -1.,
        -2.,
        2.0,
        -2.,
        1.0,
        1.0,
        1321.0,
        234.3,
        234.123,
        0.1323,
        2332e-5,
        -0x1p0
};

static const double ARR2[] = {
        1.0,
        -1.0,
        2.0,
        0.5,
        0.375,
        0.6,
        0.91267467283412345,
        1.23e4,
        2.0,
        1.0,
        -1.0,
        1.75,
        -0.9,
        2.0,
        3.0,
        3.34,
        -234.123,
        -234.3,
        2739.8,
        3.32,
        0x1.8p0
};

static const bf BF_ARR1[] = {
        bf(232, 8267349124619L | BF_MSB),
        bf(-578, 8267124619L | BF_MSB),
        bf(198, 123124134L | BF_MSB),
        bf(42, 2323L | BF_MSB),
        bf(42, 1513124123L | BF_MSB),
        bf(-192, 1234L | BF_MSB),
        bf(-8593, 123431L | BF_MSB),
        bf(823, 432L | BF_MSB),
        bf(0, BF_MSB),
};

static const bf BF_ARR2[] = {
        bf(92, 24619L | BF_MSB),
        bf(-78, 826619L | BF_MSB),
        bf(-38, 6987903412314L | BF_MSB),
        bf(92, 9123323L | BF_MSB),
        bf(2, 1301513124123L | BF_MSB),
        bf(-92, 1892045121234L | BF_MSB),
        bf(-83, 1263748123431L | BF_MSB),
        bf(83, 984231432L | BF_MSB),
        bf(0, 50000L | BF_MSB),
};

#endif //BIGFLOAT__INCLUDE_HPP
