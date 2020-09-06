# Bigfloat Library ![Unit Tests](https://github.com/Plenglin/bigfloat/workflows/Unit%20Tests/badge.svg)

High-performance, high-precision floating point library

## Disk storage

| Field     | Start | End | Notes |
|----------:|------:|----:|:------|
| Exponent  | 79    | 64  | Bias of `1023` (same as IEEE double precision) 
| Sign      | 63    | 63  | `0` is positive, `1` is negative
| Mantissa  | 62    | 0   | Technically 64 bits, with a `1` for the MSB
| **Total** | 79    | 0   | 