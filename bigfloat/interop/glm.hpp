//
// Created by astrid on 10/30/20.
//

#ifndef BIGFLOAT_PLANET_GLM_HPP
#define BIGFLOAT_PLANET_GLM_HPP

#include <bigfloat/bf.hpp>
#include <bigfloat/mat4.hpp>
#include <glm/detail/qualifier.hpp>
#include <glm/glm.hpp>

namespace glm {
    inline glm::mat4 to_float(bigfloat::mat4 &m) {
        glm::mat4 out;
        for (int i = 0; i < 4; i++) {
            auto row = __m256d(m[i]);
            for (int j = 0; j < 4; j++) {
                out[j][i] = row[j];
            }
        }
        return out;
    }
}

namespace bigfloat {
    inline bigfloat::mat4 to_bf(const glm::mat4 &m) {
        __m256d rows[4];
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                rows[j][i] = m[i][j];
            }
        }
        return bigfloat::mat4(vec4(rows[0]), vec4(rows[1]), vec4(rows[2]), vec4(rows[3]));
    }
}

#endif //BIGFLOAT_PLANET_GLM_HPP
