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
