#ifndef BIGFLOAT_MATH_HPP
#define BIGFLOAT_MATH_HPP

#include "bf.hpp"

namespace bigfloat::math {
    bf sqrt(const bf x);
    bf log(const bf x);
    bf exp(const bf x);
    bf pow(const bf b, const bf p);
    bf pow(const bf b, unsigned int p);

    bf sin(const bf x);
    bf cos(const bf x);
    bf tan(const bf x);
    bf asin(const bf x);
    bf acos(const bf x);
    bf atan(const bf x);
}

#endif //BIGFLOAT_MATH_HPP
