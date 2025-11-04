# matrixbox-c

[![Build](https://github.com/NotGoodAtC-wow/matrixbox-c/actions/workflows/cmake.yml/badge.svg)](https://github.com/NotGoodAtC-wow/matrixbox-c/actions/workflows/cmake.yml)
![License](https://img.shields.io/badge/license-MIT-informational)
![Language](https://img.shields.io/badge/language-C99-blue)
![Release](https://img.shields.io/github/v/release/NotGoodAtC-wow/matrixbox-c?display_name=tag)

A minimal matrix library in **C99**. Built with **CMake**, tested with **CTest**, row-major storage.

---

## Features (v1.0.0)
- Core API: `mat_create`, `mat_free`, `mat_get`, `mat_set`, `mat_fill`
- Operations: `mat_add`, `mat_sub`, `mat_transpose`
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

    mat_free(&A); mat_free(&B); mat_free(&C); mat_free(&T);
    return 0;
}
```

## License
MIT © NotGoodAtC-wow
