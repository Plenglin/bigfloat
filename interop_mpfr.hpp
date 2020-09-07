#ifndef BIGFLOAT_INTEROP_MPFR_HPP
#define BIGFLOAT_INTEROP_MPFR_HPP

#include <mpfr.h>
#include "bf.hpp"

void mpfr_init_set_bigfloat(mpfr_t rop, bigfloat::bf bf) {
    // TODO implement
    mpfr_init2(rop, 63);
    mpfr_set_ui_2exp(rop, bf.mantissa, bf.exponent, MPFR_RNDD);
}

#endif //BIGFLOAT_INTEROP_MPFR_HPP
