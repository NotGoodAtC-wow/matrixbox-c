#include <stdio.h>
#include "matrix.h"

int main(void) {
    Matrix A;
    if (mat_create(&A, 2, 3) != 0) {
        fprintf(stderr, "cannot allocate matrix\n");
        return 1;
    }

    mat_set(&A, 0, 0, 1.0);
    mat_set(&A, 0, 1, 2.0);
    mat_set(&A, 0, 2, 3.0);
    mat_set(&A, 1, 0, 4.0);
    mat_set(&A, 1, 1, 5.0);
    mat_set(&A, 1, 2, 6.0);

    printf("A(1,2) = %.1f\n", mat_get(&A, 1, 2)); // 6.0

    mat_free(&A);
    return 0;
}
