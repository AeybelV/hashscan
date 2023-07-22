# hashscan

hashscan is a utility for identifying hashes and other strings within large files. hashscan utilizes [Intel Hyperscan](https://github.com/intel/hyperscan) for high performance regex pattern matching.

## Hardware Requirements

- x86 32-bit or 64-bit CPU
  - Intel Streaming SIMD Extensions 3 (SSE3)
  - Intel Streaming SIMD Extensions 4.2 (SSE4.2) *optional*
  - POPCNT *optional*
  - Bit Manipulation Instructions BMI/BMI2 *optional*
  - Intel Advanced Vector Extensions 2 (AVX2) *optional*
  - Intel Advanced Vector Extensions 512 (AVX-512) *optional*

Hyperscan can make use of SSE4.2, POPCNT, BMI/BMI2, and AVX2 if present; these are determined at library compile time.

There might possibly be plans to support ARM by utilizing [Vectorscan](https://github.com/VectorCamp/vectorscan) for ARM builds.

## Dependencies

- [Intel Hyperscan](https://github.com/intel/hyperscan)
  - CMake >= 2.8.11
  - Ragel 6.9
  - Python 2.7
  - Boost >= 1.57
