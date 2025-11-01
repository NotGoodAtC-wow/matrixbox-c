#include <assert.h>
#include "matrix.h"

int main(void) {
    Matrix M;
    assert(mat_create(&M, 2, 2) == 0);
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
