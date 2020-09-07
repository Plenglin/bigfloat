//
// Created by astrid on 9/7/20.
//

#ifndef BIGFLOAT_BENCHMARK_NBODY_BODY_HPP
#define BIGFLOAT_BENCHMARK_NBODY_BODY_HPP

template<typename real>
struct body {
    real x;
    real y;
    real vx;
    real vy;
    real ax = 0;
    real ay = 0;
    real m;

    body(real m, real r, real v) : x(r), y(0), vx(0), vy(v), m(m) {

    }

    void step(real dt) {
        vx += ax * dt;
        vy += ay * dt;
        x += vx * dt;
        y += vy * dt;
    }

    real get_kinetic_energy() {
        return 0.5 * m * (vx * vx + vy * vy);
    }
};


#endif //BIGFLOAT_BENCHMARK_NBODY_BODY_HPP
