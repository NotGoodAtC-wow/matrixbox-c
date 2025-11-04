#include "matrix.h"
#include <stdlib.h>

int mat_create(Matrix* m, size_t rows, size_t cols) {
    if (!m) return -1;
    m->rows = rows;
    m->cols = cols;

    if (rows == 0 || cols == 0) {
        m->data = NULL;
        return 0;
    }

    m->data = (double*)calloc(rows * cols, sizeof(double));
    return m->data ? 0 : -1;
}

void mat_free(Matrix* m) {
    if (!m) return;
    free(m->data);
    m->data = NULL;
    m->rows = 0;
    m->cols = 0;
}

double mat_get(const Matrix* m, size_t i, size_t j) {
    if (!m || !m->data) return 0.0;            // защита от NULL
    if (i >= m->rows || j >= m->cols) return 0.0; // защита от выхода
    return m->data[i * m->cols + j];
}

void mat_set(Matrix* m, size_t i, size_t j, double v) {
    if (!m || !m->data) return;                // защита от NULL
    if (i >= m->rows || j >= m->cols) return;  // защита от выхода
    m->data[i * m->cols + j] = v;
}

void mat_fill(Matrix* m, double v) {
    if (!m || !m->data) return;
    size_t n = m->rows * m->cols;
    for (size_t k = 0; k < n; ++k) {
        m->data[k] = v;
    }
}
// v1 after
static int _valid(const Matrix* m) {
    return m && m->data && m->rows > 0 && m->cols > 0;
}

int mat_add(const Matrix* A, const Matrix* B, Matrix* C) {
    if (!_valid(A) || !_valid(B) || !_valid(C)) return -1;
    if (A->rows != B->rows || A->cols != B->cols) return -2;
    if (C->rows != A->rows || C->cols != A->cols) return -3;
    size_t n = (size_t)A->rows * A->cols;
    for (size_t k = 0; k < n; ++k) C->data[k] = A->data[k] + B->data[k];
    return 0;
}

int mat_sub(const Matrix* A, const Matrix* B, Matrix* C) {
    if (!_valid(A) || !_valid(B) || !_valid(C)) return -1;
    if (A->rows != B->rows || A->cols != B->cols) return -2;
    if (C->rows != A->rows || C->cols != A->cols) return -3;
    size_t n = (size_t)A->rows * A->cols;
    for (size_t k = 0; k < n; ++k) C->data[k] = A->data[k] - B->data[k];
    return 0;
}

int mat_transpose(const Matrix* A, Matrix* T) {
    if (!_valid(A) || !_valid(T)) return -1;
    if (T->rows != A->cols || T->cols != A->rows) return -3;
    for (size_t i = 0; i < A->rows; ++i)
        for (size_t j = 0; j < A->cols; ++j)
            T->data[j * T->cols + i] = A->data[i * A->cols + j];
    return 0;
}

/* matrix multiplication: C = A * B
   Shapes: A (r x k), B (k x c) => C (r x c)
   Returns: 0 ok; -1 invalid args; -2 incompatible inner dims; -3 wrong C shape */
int mat_mul(const Matrix* A, const Matrix* B, Matrix* C) {
    if (!_valid(A) || !_valid(B) || !_valid(C)) return -1;
    if (A->cols != B->rows) return -2;
    if (C->rows != A->rows || C->cols != B->cols) return -3;

    const size_t r = A->rows, k = A->cols, c = B->cols;

    for (size_t i = 0; i < r; ++i) {
        for (size_t j = 0; j < c; ++j) {
            double s = 0.0;
            for (size_t t = 0; t < k; ++t) {
                s += A->data[i * A->cols + t] * B->data[t * B->cols + j];
            }
            C->data[i * C->cols + j] = s;
        }
    }
    return 0;
}

/* in-place scalar multiply: A *= k
   Returns: 0 ok; -1 invalid args */
int mat_mul_scalar(Matrix* A, double k) {
    if (!_valid(A)) return -1;
    const size_t n = A->rows * A->cols;
    for (size_t idx = 0; idx < n; ++idx) {
        A->data[idx] *= k;
    }
    return 0;
}

/* ==== v3: Gaussian elimination helpers (internal) ==== */

static double _dabs(double x) { return x < 0 ? -x : x; }

static void _swap_rows(Matrix* M, size_t i, size_t j) {
    if (i == j || !M || !_valid(M)) return;
    const size_t n = M->cols;
    for (size_t c = 0; c < n; ++c) {
        double tmp = M->data[i * n + c];
        M->data[i * n + c] = M->data[j * n + c];
        M->data[j * n + c] = tmp;
    }
}

/* In-place conversion to (row-)upper echelon form with partial pivoting.
   Returns number of pivots; writes swap parity (0 even, 1 odd) if parity!=NULL. */
static int _to_upper_echelon(Matrix* R, double eps, int* parity) {
    if (!_valid(R)) { if (parity) *parity = 0; return 0; }
    size_t r = R->rows, c = R->cols;
    size_t row = 0, col = 0;
    int pivots = 0;
    int swaps = 0;

    while (row < r && col < c) {
        /* choose pivot row by max |value| in current column */
        size_t piv = row;
        double best = _dabs(R->data[row * c + col]);
        for (size_t i = row + 1; i < r; ++i) {
            double v = _dabs(R->data[i * c + col]);
            if (v > best) { best = v; piv = i; }
        }
        if (best <= eps) { /* column is (near) zero -> skip column */
            ++col;
            continue;
        }
        if (piv != row) { _swap_rows(R, piv, row); swaps ^= 1; }

        /* eliminate below */
        double pivot = R->data[row * c + col];
        for (size_t i = row + 1; i < r; ++i) {
            double a = R->data[i * c + col];
            if (_dabs(a) <= eps) continue;
            double f = a / pivot;
            for (size_t j = col; j < c; ++j) {
                R->data[i * c + j] -= f * R->data[row * c + j];
            }
        }
        ++row; ++col; ++pivots;
    }
    if (parity) *parity = swaps & 1;
    return pivots;
}

/* ==== public v3 API ==== */

int mat_det(const Matrix* A, double* out, double eps) {
    if (!out) return -1;
    *out = 0.0;
    if (!_valid(A)) return -1;
    if (A->rows != A->cols) return -2; /* not square */

    size_t n = A->rows;
    if (n == 0) { *out = 1.0; return 0; } /* det of 0x0 = 1 */

    /* make a working copy */
    Matrix R;
    if (mat_create(&R, A->rows, A->cols) != 0) return -1;
    for (size_t i = 0; i < n * n; ++i) R.data[i] = A->data[i];

    int parity = 0;
    int pivots = _to_upper_echelon(&R, eps, &parity);

    if (pivots < (int)n) { /* singular */
        *out = 0.0;
        mat_free(&R);
        return 0;
    }

    double prod = 1.0;
    for (size_t i = 0; i < n; ++i) {
        prod *= R.data[i * n + i];
    }
    if (parity) prod = -prod;

    *out = prod;
    mat_free(&R);
    return 0;
}

int mat_rank(const Matrix* A, size_t* out, double eps) {
    if (!out) return -1;
    *out = 0;
    if (!_valid(A)) return -1;

    Matrix R;
    if (mat_create(&R, A->rows, A->cols) != 0) return -1;
    /* copy */
    for (size_t i = 0, n = A->rows * A->cols; i < n; ++i) R.data[i] = A->data[i];

    int parity_dummy = 0;
    int pivots = _to_upper_echelon(&R, eps, &parity_dummy);
    *out = (pivots < 0) ? 0u : (size_t)pivots;

    mat_free(&R);
    return 0;
}
