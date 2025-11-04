#include <assert.h>
#include "matrix.h"

// простая проверка без <math.h>
static int deq(double a, double b) {
    double d = a - b; if (d < 0) d = -d; return d < 1e-9;
}

static void fill_seq(Matrix* M, const double* vals) {
    for (size_t i = 0; i < M->rows; ++i)
        for (size_t j = 0; j < M->cols; ++j)
            mat_set(M, i, j, vals[i * M->cols + j]);
}

int main(void) {
    // Case 1: (2x3) * (3x2) = (2x2)
    Matrix A; assert(mat_create(&A, 2, 3) == 0);
    Matrix B; assert(mat_create(&B, 3, 2) == 0);
    Matrix C; assert(mat_create(&C, 2, 2) == 0);

    const double a[] = {1,2,3, 4,5,6};          // 2x3
    const double b[] = {7,8, 9,10, 11,12};      // 3x2
    fill_seq(&A, a);
    fill_seq(&B, b);

    assert(mat_mul(&A, &B, &C) == 0);
    // expected: [[58, 64],[139,154]]
    assert(deq(mat_get(&C,0,0), 58));
    assert(deq(mat_get(&C,0,1), 64));
    assert(deq(mat_get(&C,1,0), 139));
    assert(deq(mat_get(&C,1,1), 154));

    // Case 2: I*X = X and X*I = X
    Matrix I; assert(mat_create(&I, 2, 2) == 0);
    mat_fill(&I, 0.0);
    mat_set(&I, 0, 0, 1.0);
    mat_set(&I, 1, 1, 1.0);

    Matrix X; assert(mat_create(&X, 2, 2) == 0);
    const double xv[] = {3,4, 5,6};
    fill_seq(&X, xv);

    Matrix R; assert(mat_create(&R, 2, 2) == 0);
    assert(mat_mul(&I, &X, &R) == 0);
    assert(deq(mat_get(&R,0,0), 3) && deq(mat_get(&R,0,1), 4)
        && deq(mat_get(&R,1,0), 5) && deq(mat_get(&R,1,1), 6));
    assert(mat_mul(&X, &I, &R) == 0);
    assert(deq(mat_get(&R,0,0), 3) && deq(mat_get(&R,0,1), 4)
        && deq(mat_get(&R,1,0), 5) && deq(mat_get(&R,1,1), 6));

    // Case 3: incompatible inner dims
    Matrix A2; assert(mat_create(&A2, 2, 2) == 0);
    Matrix B2; assert(mat_create(&B2, 3, 3) == 0);
    Matrix C2; assert(mat_create(&C2, 2, 3) == 0);
    assert(mat_mul(&A2, &B2, &C2) == -2);

    // Case 4: wrong C shape
    Matrix A3; assert(mat_create(&A3, 1, 2) == 0);
    Matrix B3; assert(mat_create(&B3, 2, 1) == 0);
    Matrix C3_wrong; assert(mat_create(&C3_wrong, 1, 2) == 0); // must be 1x1
    assert(mat_mul(&A3, &B3, &C3_wrong) == -3);

    // Case 5: scalar multiply
    Matrix S; assert(mat_create(&S, 2, 2) == 0);
    const double sv[] = {1,2, 3,4};
    fill_seq(&S, sv);
    assert(mat_mul_scalar(&S, 2.0) == 0);
    assert(deq(mat_get(&S,0,0), 2) && deq(mat_get(&S,0,1), 4)
        && deq(mat_get(&S,1,0), 6) && deq(mat_get(&S,1,1), 8));

    mat_free(&A); mat_free(&B); mat_free(&C);
    mat_free(&I); mat_free(&X); mat_free(&R);
    mat_free(&A2); mat_free(&B2); mat_free(&C2);
    mat_free(&A3); mat_free(&B3); mat_free(&C3_wrong);
    mat_free(&S);
    return 0;
}
