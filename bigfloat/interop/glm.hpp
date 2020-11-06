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
    template<qualifier Q>
    struct mat<4, 4, bigfloat::bf, Q> : bigfloat::mat4 {
        mat() : bigfloat::mat4() {}
        mat(bigfloat::bf x) : bigfloat::mat4(x) {}

        glm::mat4 to_float() {
            glm::mat4 out;
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    out[i][j] = float(bigfloat::bf((*this)[i][j]));
                }
            }
            return out;
        }
    };
    using bfmat4 = mat<4, 4, bigfloat::bf, defaultp>;

    template<int n, qualifier Q>
    struct vec<n, bigfloat::bf, Q> : bigfloat::vec4 {
        explicit vec(bigfloat::bf x0, bigfloat::bf x1 = 0, bigfloat::bf x2 = 0, bigfloat::bf x3 = 0) : bigfloat::vec4(x0, x1, x2, x3) {

        }

        inline vec<n, bigfloat::bf, Q> operator *(vec<n, bigfloat::bf, Q> &other) {
            return bigfloat::vec4::operator*(*this, other);
        }

        inline vec<n, bigfloat::bf, Q> operator +(vec<n, bigfloat::bf, Q> &other) {
            return bigfloat::vec4::operator*(*this, other);
        }
    };
    using bfvec4 = vec<4, bigfloat::bf, defaultp>;

    template<qualifier Q>
    struct vec<3, bigfloat::bf, Q> : bigfloat::vec4 {
        vec(bigfloat::bf x, bigfloat::bf y, bigfloat::bf z) : bigfloat::vec4(x, y, z, 1) {}
    };
    using bfvec3 = vec<3, bigfloat::bf, defaultp>;

    template<qualifier Q>
    struct vec<2, bigfloat::bf, Q> : bigfloat::vec4 {
        vec(bigfloat::bf x, bigfloat::bf y) : bigfloat::vec4(x, y, 1, 0) {}
    };
    using bfvec2 = vec<2, bigfloat::bf, defaultp>;
}

#endif //BIGFLOAT_PLANET_GLM_HPP
