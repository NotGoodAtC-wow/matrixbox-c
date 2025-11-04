# matrixbox-c — v2.0.0 (v2) • 2025-11-04

# HIGHLIGHTS
#   • New matrix multiplication: mat_mul  → C = A * B  (with shape checks)
#   • In-place scalar multiply: mat_mul_scalar  → A *= k
#   • New tests: test_mul  (2x3*3x2, identity, and error paths)
#
# COMPATIBILITY
#   • Language: C99
#   • Storage: row-major, indexing: data[i*cols + j]
#   • API remains backward compatible with v1.0.0
#
# CI
#   • GitHub Actions (Ubuntu); verified locally on Windows (MinGW)
