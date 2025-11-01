#include <assert.h>
#include "matrix.h"

int main(void) {
    Matrix M;
    int rc = mat_create(&M, 2, 2);
    assert(rc == 0);
    assert(M.data != NULL);
    assert(M.rows == 2 && M.cols == 2);

    mat_set(&M, 0, 0, 10.0);
    mat_set(&M, 0, 1, 20.0);
    mat_set(&M, 1, 0, 30.0);
    mat_set(&M, 1, 1, 40.0);

    assert(mat_get(&M, 0, 0) == 10.0);
    assert(mat_get(&M, 1, 1) == 40.0);

    mat_fill(&M, 5.0);
    assert(mat_get(&M, 0, 0) == 5.0);
    assert(mat_get(&M, 1, 1) == 5.0);

    mat_free(&M);
    return 0;
}
