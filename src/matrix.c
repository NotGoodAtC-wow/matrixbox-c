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
    m->rows = m->cols = 0;
}

double mat_get(const Matrix* m, size_t i, size_t j) {
    return m->data[i * m->cols + j];
}

void mat_set(Matrix* m, size_t i, size_t j, double v) {
    m->data[i * m->cols + j] = v;
}

void mat_fill(Matrix* m, double v) {
    if (!m || !m->data) return;
    size_t n = m->rows * m->cols;
    for (size_t k = 0; k < n; ++k) {
        m->data[k] = v;
    }
}
