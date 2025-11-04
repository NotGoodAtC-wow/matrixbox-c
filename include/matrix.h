#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>  // size_t

// Row-major matrix
typedef struct {
    size_t rows;
    size_t cols;
    double* data;
} Matrix;

/* constructors / destructors */
int  mat_create(Matrix* m, size_t rows, size_t cols);   // 0 ok; -1 bad args; -2 alloc fail
void mat_free(Matrix* m);

/* accessors */
double mat_get(const Matrix* m, size_t i, size_t j);    // guarded
void   mat_set(Matrix* m,       size_t i, size_t j, double v); // guarded
void   mat_fill(Matrix* m, double v);

/* v1 ops */
int mat_add(const Matrix* A, const Matrix* B, Matrix* C);      // C = A + B
int mat_sub(const Matrix* A, const Matrix* B, Matrix* C);      // C = A - B
int mat_transpose(const Matrix* A, Matrix* T);                 // T = A^T

/* v2 ops */
int mat_mul(const Matrix* A, const Matrix* B, Matrix* C);      // C = A * B
int mat_mul_scalar(Matrix* A, double k);                       // A *= k (in-place)

/* v3 Gaussian */
int mat_det (const Matrix* A, double* out, double eps);        // 0 ok; -2 non-square
int mat_rank(const Matrix* A, size_t* out, double eps);        // 0 ok

#endif /* MATRIX_H */
