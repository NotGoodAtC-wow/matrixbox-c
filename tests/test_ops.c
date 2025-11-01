#include <assert.h>
#include "matrix.h"

// простая абсолютная разность без <math.h>
static int deq(double a, double b) {
    double d = a - b;
    if (d < 0) d = -d;
    return d < 1e-9;
}

int main(void) {
    // A (2x3)
    Matrix A; assert(mat_create(&A, 2, 3) == 0);
    double a[] = {1,2,3, 4,5,6};
    for (size_t i=0;i<2;i++) for (size_t j=0;j<3;j++) mat_set(&A,i,j,a[i*3+j]);

    // B (2x3)
    Matrix B; assert(mat_create(&B, 2, 3) == 0);
    double b[] = {6,5,4, 3,2,1};
    for (size_t i=0;i<2;i++) for (size_t j=0;j<3;j++) mat_set(&B,i,j,b[i*3+j]);

    // C = A + B
    Matrix C; assert(mat_create(&C, 2, 3) == 0);
    assert(mat_add(&A,&B,&C) == 0);
    double sum_expected[] = {7,7,7, 7,7,7};
    for (size_t i=0;i<2;i++) for (size_t j=0;j<3;j++)
        assert(deq(mat_get(&C,i,j), sum_expected[i*3+j]));

    // D = A - B
    Matrix D; assert(mat_create(&D, 2, 3) == 0);
    assert(mat_sub(&A,&B,&D) == 0);
    double sub_expected[] = {-5,-3,-1, 1,3,5};
    for (size_t i=0;i<2;i++) for (size_t j=0;j<3;j++)
        assert(deq(mat_get(&D,i,j), sub_expected[i*3+j]));

    // T = A^T (3x2)
    Matrix T; assert(mat_create(&T, 3, 2) == 0);
    assert(mat_transpose(&A,&T) == 0);
    assert(deq(mat_get(&T,0,0), 1));
    assert(deq(mat_get(&T,1,0), 2));
    assert(deq(mat_get(&T,2,1), 6));

    mat_free(&A); mat_free(&B); mat_free(&C); mat_free(&D); mat_free(&T);
    return 0;
}
