# Changelog
All notable changes to this project will be documented in this file.

The format follows [Keep a Changelog](https://keepachangelog.com/en/1.1.0/)
and the project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]
### Planned
- `mat_mul` (matrix multiplication) and `mat_mul_scalar`
- Gaussian elimination, `mat_det`, `mat_rank`
- Matrix I/O (read/write) and simple CLI commands

## [1.0.0] - 2025-11-02
### Added
- Matrix library in **C99** with row-major storage.
- Core API:
  - `mat_create`, `mat_free`
  - `mat_get`, `mat_set`, `mat_fill`
  - `mat_add`, `mat_sub`, `mat_transpose`
- Demo executable: `matrixlab_demo`.
- Test suites: `test_matrix`, `test_ops` (CTest).
- GitHub Actions CI: build & test on each push/PR (Ubuntu).

### Fixed
- Segfault on Linux CI caused by `<math.h>`/`libm` usage in tests — removed dependency.

### Notes
- Indexing formula: `data[i*cols + j]`.
- Verified on Windows locally (MinGW) and Ubuntu in CI.

[Unreleased]: https://github.com/<YOUR_USER>/<YOUR_REPO>/compare/v1.0.0...HEAD
[1.0.0]: https://github.com/<YOUR_USER>/<YOUR_REPO>/releases/tag/v1.0.0
