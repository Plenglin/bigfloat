//
// Created by astrid on 9/19/20.
//

#ifndef BIGFLOAT_BOOST_INTEROP_HPP
#define BIGFLOAT_BOOST_INTEROP_HPP

#include <boost/test/tools/floating_point_comparison.hpp>
#include "bf.hpp"

using namespace bigfloat;

namespace boost::math::fpc::fpc_detail {
    template<>
    struct fpt_limits<bf> {
        static bf max_value() {
            return bf::max_value();
        }

        static bf min_value() {
            return bf::min_value();
        }
    };
}

#endif //BIGFLOAT_BOOST_INTEROP_HPP
