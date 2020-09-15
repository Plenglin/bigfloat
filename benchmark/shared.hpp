//
// Created by astrid on 9/14/20.
//

#ifndef BIGFLOAT_SHARED_HPP
#define BIGFLOAT_SHARED_HPP

#define NUMBERS_A {98127, 0.9123478, 9.923645, -2.834679, 1.134598, -98245.932458}
#define NUMBERS_B {1.1243e8, 84123.120734, -982314.238, -192, 9182.1234, 891.23456}
#define NUMBERS_COUNT 6

#include "../bf.hpp"

using namespace bigfloat;

const static bf bf_as[] = NUMBERS_A;
const static bf bf_bs[] = NUMBERS_B;

const static double d_as[] = NUMBERS_A;
const static double d_bs[] = NUMBERS_B;


#endif //BIGFLOAT_SHARED_HPP
