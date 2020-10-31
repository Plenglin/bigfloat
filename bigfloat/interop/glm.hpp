//
// Created by astrid on 10/30/20.
//

#ifndef BIGFLOAT_PLANET_GLM_HPP
#define BIGFLOAT_PLANET_GLM_HPP

#include <bigfloat/bf.hpp>
#include <bigfloat/mat4.hpp>
#include <glm/detail/qualifier.hpp>

namespace glm {
    template<qualifier Q>
    struct mat<4, 4, bigfloat::bf, Q> : bigfloat::mat4 {};
}

#endif //BIGFLOAT_PLANET_GLM_HPP
