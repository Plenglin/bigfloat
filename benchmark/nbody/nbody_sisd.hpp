//
// Created by astrid on 9/7/20.
//

#ifndef BIGFLOAT_BENCHMARK_NBODY_NBODY_SISD_HPP
#define BIGFLOAT_BENCHMARK_NBODY_NBODY_SISD_HPP

#include <vector>
#include "body.hpp"
#include "util.hpp"

template <typename real>
class nbody_bf_simd {
    const real G = real(6.67430e-11);
    std::vector<body<real>> bodies = {
            body(real(0.33e24),      real(46e9),        real(47.4e3)),
            body(real(4.87e24),      real(108.2e9),     real(35.0e3)),
            body(real(5.97e24),      real(149.6e9),     real(29.8e3)),
            body(real(0.642e24),     real(227.9e9),     real(24.1e3)),
            body(real(1898e24),      real(778.6e9),     real(13.1e3)),
            body(real(568e24),       real(1433.5e9),    real(9.7e3)),
            body(real(86.8e24),      real(2872.5e9),    real(6.8e3)),
            body(real(102e24),       real(4495.1e9),    real(5.4e3)),
            body(real(0.0146e24),    real(5906.4e9),    real(4.7e3)),
    };
public:
    void step(real dt) {
        for (auto b1 = bodies.begin(); b1 != bodies.end(); b1++) {
            real ax = real(0);
            real ay = real(0);
            real x1 = b1->x;
            real y1 = b1->y;

            for (auto b2 = bodies.begin(); b2 != bodies.end(); b2++) {
                if (b1 == b2) continue;

                real dx = x1 - b2->x;
                real dy = x1 - b2->y;
                real r2 = dx * dx + dy * dy;
                real ag = G * b2->m / r2;
                real r = t_sqrt(r2);
                real scl = ag / r;
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

    real get_total_energy() {
        real energy = real(0);

        for (auto b1: bodies) {
            energy += b1->get_kinetic_energy();

            real pe = real(0);
            for (auto b2: bodies) {
                if (b1 == b2) continue;

                real dx = b1.x - b2.x;
                real dy = b1.y - b2.y;
                real r2 = dx * dx + dy * dy;
                real r = t_sqrt(r2);
                real pg = G * b2.m / r;
                pe += pg;
            }

            energy += pe * b1.mass;
        }

        return energy;
    }
};


#endif //BIGFLOAT_BENCHMARK_NBODY_NBODY_SISD_HPP
