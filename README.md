===== README.md =====
# matrixbox-c

[![Build](https://github.com/NotGoodAtC-wow/matrixbox-c/actions/workflows/cmake.yml/badge.svg)](https://github.com/NotGoodAtC-wow/matrixbox-c/actions/workflows/cmake.yml)
![License](https://img.shields.io/badge/license-MIT-informational)
![Language](https://img.shields.io/badge/language-C99-blue)
![Release](https://img.shields.io/github/v/release/NotGoodAtC-wow/matrixbox-c?display_name=tag)

A minimal matrix library in **C99**. Built with **CMake**, tested with **CTest**, row-major storage.

---

## Features (v2.0.0)
- Core API: `mat_create`, `mat_free`, `mat_get`, `mat_set`, `mat_fill`
- Operations: `mat_add`, `mat_sub`, `mat_transpose`, `mat_mul`
- In-place ops: `mat_mul_scalar`
- Defensive checks for `NULL`/bounds in accessors
- Demo executable: `matrixlab_demo`
- CI on GitHub Actions (Ubuntu); verified locally on Windows (MinGW)

---

## Build

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

## Test

```bash
cmake --build build --target test
# or with verbose output:
ctest --test-dir build --output-on-failure
```

## Quick usage

```c
#include "matrix.h"
#include <stdio.h>

int main(void) {
    Matrix A, B, C, T;

    mat_create(&A, 2, 2);
    mat_create(&B, 2, 2);
    mat_create(&C, 2, 2);
    mat_create(&T, 2, 2);

    mat_set(&A, 0, 0, 1); mat_set(&A, 0, 1, 2);
    mat_set(&A, 1, 0, 3); mat_set(&A, 1, 1, 4);

    mat_fill(&B, 1.0);            // all ones
    mat_add(&A, &B, &C);          // C = A + B
    mat_transpose(&C, &T);        // T = C^T
    printf("T(1,0) = %.1f\n", mat_get(&T, 1, 0)); // -> 3.0

    // multiplication example: (2x2)*(2x2) -> (2x2)
    Matrix M; mat_create(&M, 2, 2);
    mat_mul(&A, &B, &M);          // M = A * B

    // in-place scalar multiply
    mat_mul_scalar(&M, 0.5);      // M *= 0.5

    mat_free(&A); mat_free(&B); mat_free(&C); mat_free(&T); mat_free(&M);
    return 0;
}
```

## API(Overview)

| Function                                                   | Description                                                             |
| ---------------------------------------------------------- | ----------------------------------------------------------------------- |
| `int mat_create(Matrix* m, size_t rows, size_t cols)`      | Allocate `rows×cols` matrix (zero-initialized). Returns `0` on success. |
| `void mat_free(Matrix* m)`                                 | Free data and reset shape to `0×0`.                                     |
| `double mat_get(const Matrix* m, size_t i, size_t j)`      | Get element *(row-major; guarded)*.                                     |
| `void mat_set(Matrix* m, size_t i, size_t j, double v)`    | Set element *(guarded)*.                                                |
| `void mat_fill(Matrix* m, double v)`                       | Fill all elements with `v`.                                             |
| `int mat_add(const Matrix* A, const Matrix* B, Matrix* C)` | `C = A + B` (same shape).                                               |
| `int mat_sub(const Matrix* A, const Matrix* B, Matrix* C)` | `C = A - B` (same shape).                                               |
| `int mat_transpose(const Matrix* A, Matrix* T)`            | `T = A^T` (shape `cols×rows`).                                          |
| `int mat_mul(const Matrix* A, const Matrix* B, Matrix* C)` | `C = A * B` (A: `r×k`, B: `k×c`, C: `r×c`).                             |
| `int mat_mul_scalar(Matrix* A, double k)`                  | In-place scalar multiply: `A *= k`.                                     |

## Project layout

```bash
.
├─ include/            # public API: matrix.h
├─ src/                # implementation + demo
├─ tests/              # CTest suites
├─ .github/workflows/  # CI (cmake.yml)
└─ CMakeLists.txt
```

## Roadmap

- v3: Gaussian elimination, `mat_det`, `mat_rank`
- v4: Matrix I/O (read/write) and simple CLI
