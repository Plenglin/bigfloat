//
// Created by astrid on 9/27/20.
//

#ifndef BIGFLOAT_NBODY_BF_SIMD_HPP
#define BIGFLOAT_NBODY_BF_SIMD_HPP

#include <vector>
#include "../../src/bigfloat.hpp"
#include "body.hpp"
#include "../../src/simd.hpp"

using namespace bigfloat;
using namespace bigfloat::simd;

const bf G = bf(6.67430e-11);
const std::vector<bf> mass_vector = std::vector {
        bf(0.33e24),
        bf(4.87e24),
        bf(5.97e24),
        bf(0.642e24),
        bf(1898e24),
        bf(568e24),
        bf(86.8e24),
        bf(102e24),
        bf(0.0146e24)
};
const std::vector<bf> radius_vector = std::vector {
        bf(46e9),
        bf(108.2e9),
        bf(149.6e9),
        bf(227.9e9),
        bf(778.6e9),
        bf(1433.5e9),
        bf(2872.5e9),
        bf(4495.1e9),
        bf(5906.4e9)
};
const std::vector<bf> velocity_vector = std::vector {
        bf(47.4e3),
        bf(35.0e3),
        bf(29.8e3),
        bf(24.1e3),
        bf(13.1e3),
        bf(9.7e3),
        bf(6.8e3),
        bf(5.4e3),
        bf(4.7e3)
};

class nbody_bf_simd {
    vecn radius = vecn(radius_vector.begin(), radius_vector.end());
    vecn mass = vecn(mass_vector.begin(), mass_vector.end());
    vecn velocity = vecn(velocity_vector.begin(), velocity_vector.end());
public:
    void step(bf dt) {
        for (auto b1 = bodies.begin(); b1 != bodies.end(); b1++) {
            bf ax = bf(0);
            bf ay = bf(0);
            bf x1 = b1->x;
            bf y1 = b1->y;

            for (auto b2 = bodies.begin(); b2 != bodies.end(); b2++) {
                if (b1 == b2) continue;

                bf dx = x1 - b2->x;
                bf dy = x1 - b2->y;
                bf r2 = dx * dx + dy * dy;
                bf ag = G * b2->m / r2;
                bf r = t_sqrt(r2);
                bf scl = ag / r;
                ax += -dx * scl;
                ay += -dy * scl;
            }

            b1->ax = ax;
            b1->ay = ay;
        }

        for (auto body: bodies) {
            body.step(dt);
        }
    }
};

#endif //BIGFLOAT_NBODY_BF_SIMD_HPP
