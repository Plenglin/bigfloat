#ifndef BIGFLOAT__INCLUDE_HPP
#define BIGFLOAT__INCLUDE_HPP

#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
#include "../bigfloat.hpp"

using namespace std;
using namespace bigfloat;
namespace data = boost::unit_test::data;
namespace mono = data::monomorphic;

#define DOUBLE_TOLERANCE 1e-10

static const double ARR1[] = {
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
        0.1323,
        2332e-5
};

static const double ARR2[] = {
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
        2739.8,
        3.32
};

#endif //BIGFLOAT__INCLUDE_HPP
