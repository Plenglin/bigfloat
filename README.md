# Bigfloat Library ![Unit Tests](https://github.com/Plenglin/bigfloat/workflows/Verification/badge.svg)

High-performance, high-precision floating point library

## Useful Links

- [Bigfloat benchmark times](https://astrid.tech/bigfloat/dev/bench/)
- [What Is Astrid Working On?](https://github.com/Plenglin/bigfloat/projects/1)

## Useful References
- [C++ Optimization Strategies and Techniques (slightly outdated)](https://www.tantalon.com/pete/cppopt/main.htm)
- [Coding Practices which enable the compiler/optimizer to make a faster program (StackOverflow)](https://stackoverflow.com/q/2074099/12947037)
- [What Every Computer Scientist Should Know About Floating-Point Arithmetic](https://docs.oracle.com/cd/E19957-01/806-3568/ncg_goldberg.html)

## Packed Format

Likely would be used when sending over networks and such.

| Field     | Start | End | Count | Notes |
|----------:|------:|----:|------:|:------|
| Exponent  | 79    | 64  | 16    | Bias of `1023` (same as IEEE double precision) 
| Sign      | 63    | 63  | 1     | `0` is positive, `1` is negative
| Mantissa  | 62    | 0   | 63    | Technically 64 bits, with a `1` for the MSB
| **Total** | 79    | 0   | 80    | This is 10 bytes, or 2 more than a double.
