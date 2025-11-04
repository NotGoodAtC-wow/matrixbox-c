#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>

typedef struct {
    size_t rows;
    size_t cols;
    double* data;   // row-major: a[i,j] = data[i*cols + j]
} Matrix;

/* создание пустой матрицы rows×cols, память под элементы = 0
   вернёт 0 при успехе, не 0 при ошибке */
int mat_create(Matrix* m, size_t rows, size_t cols);

/* освободить память */
void mat_free(Matrix* m);

/* получить элемент (без проверок ради скорости) */
double mat_get(const Matrix* m, size_t i, size_t j);

/* установить элемент */
void mat_set(Matrix* m, size_t i, size_t j, double v);

/* заполнить константой */
void mat_fill(Matrix* m, double v);

int mat_add(const Matrix* A, const Matrix* B, Matrix* C);        // C = A + B
int mat_sub(const Matrix* A, const Matrix* B, Matrix* C);        // C = A - B
int mat_transpose(const Matrix* A, Matrix* T);                   // T = A^T
int mat_mul(const Matrix* A, const Matrix* B, Matrix* C);   // C = A * B
int mat_mul_scalar(Matrix* A, double k);                     // A *= k

#endif
