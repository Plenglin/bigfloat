# Notes on algorithms used

For all operations on some variable named `a`, the following notation shall be used:

- `uint64 mta` = mantissa of `a`
- `uint16 exa` = exponent of `a`
- `bool sa` = sign of `a`

We will always assume variable `o` to be the return value. Thus, `so`, `mto`, and `exo` are the fields of the return value.

In addition, the following constants are assumed:

- `BIAS = 1023` the exponent bias

The machine is assumed to be **little endian** like all x86 systems. 

This document may look like it's me doing good coding practices and documenting my work, but honestly, it's just here to lay out my ideas.

## `a * b`

1. If either a or b is zero, return 0.
2. `uint128 mul := mta * mtb`
3. `int32 leading_zeros = ` the number of leading zeros in the upper bits of `mul`.
4. `mto := mul >> (64 - leading_zeros)` (Shift the most significant 1 to bit 63)
5. `exo := exa + exb - leading_zeros - BIAS - 1` (Add exponents, normalize based on leading zeros, and debias)
6. `so := sa ^ sb`

### Vectorization of `a[4] * b[4]`

1. Unsure how I'd check for zero. Likely perform a broadcast equal to 0, and mask it at the end 
2. How to get `mul`?
    - Using [this method](https://stackoverflow.com/a/28904636/12947037), omitting the carry flag, broadcast multiply `a` and `b` together. Summarized, `result = ahi * bhi + (alo * bhi >> 32) + (ahi * blo >> 32)` (what is written here is incomplete, maybe lets _not_ do this...) 
        1. `mllhh := a * b` along `32`s (holds `alo * blo` and `ahi * bhi`) (`_mm_mul_epi32`)
        2. `ahhll := a` permuted along `32`s by `10325476` (holds `hi` and `lo` in that order)
        3. `mhllh := ahhll * b` along `32`s (holds `ahi * blo` and `alo * bhi`, in that order, for each `int64`)
        4. `shlhh := ` blend `mllhh` and `mhllh` keeping bits 1, 3, 5, 7 from `mllhh` and 0, 2, 4, 6 from `mhllh` 
        5. `slh00 := mhllh` permuted along `32`s by `1x3x5x7x` where `x`s can be anything, then the `x`s are replaced with `0`s
        6. `mul := shlhh + slh00` along `64`s
    - Or, straight-up `int128` multiplication, but break into 2 `m256`s. (Unfortunately no vectorized `int128 * int128` instructions :frowning:)
        1. 