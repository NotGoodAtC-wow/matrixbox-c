# =============================================================================
# matrixbox-c — Changelog
# Version: v2.0.0 (v2) — 2025-11-04
# =============================================================================
# Added
# - mat_mul (matrix multiplication): C = A * B with shape checks.
# - mat_mul_scalar (in-place scalar multiply): A *= k.
# - Test suite: test_mul (covers 2x3 * 3x2, identity cases, error paths).
#
# Notes
# - Language: C99. Row-major storage; indexing: data[i*cols + j].
# - API is backward compatible with v1.0.0.
# - CI: GitHub Actions (Ubuntu); verified locally on Windows (MinGW).
#
# Breaking changes
# - None.
#
# Links
# - Release: https://github.com/NotGoodAtC-wow/matrixbox-c/releases/tag/v1.1.0
# - Compare: https://github.com/NotGoodAtC-wow/matrixbox-c/compare/v1.0.0...v1.1.0
# =============================================================================
