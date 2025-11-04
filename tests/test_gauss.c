#include <assert.h>
#include "matrix.h"

/* tiny abs without <math.h> */
static int deq(double a, double b) { double d = a - b; if (d < 0) d = -d; return d < 1e-9; }

static void set_id(Matrix* M) {
    assert(M->rows == M->cols);
    for (size_t i = 0; i < M->rows; ++i)
        for (size_t j = 0; j < M->cols; ++j)
            mat_set(M, i, j, (i == j) ? 1.0 : 0.0);
}

static void set_from(Matrix* M, const double* vals) {
    for (size_t i = 0; i < M->rows; ++i)
        for (size_t j = 0; j < M->cols; ++j)
            mat_set(M, i, j, vals[i * M->cols + j]);
}

int main(void) {
    const double EPS = 1e-9;

    /* det 2x2: [[1,2],[3,4]] -> -2 */
    {
        Matrix A; assert(mat_create(&A, 2, 2) == 0);
        const double v[] = {1,2,3,4};
        set_from(&A, v);
        double d = 0.0;
        assert(mat_det(&A, &d, EPS) == 0);
        assert(deq(d, -2.0));
        mat_free(&A);
    }

    /* det I3 = 1 */
    {
        Matrix I; assert(mat_create(&I, 3, 3) == 0);
        set_id(&I);
        double d = 0.0;
        assert(mat_det(&I, &d, EPS) == 0);
        assert(deq(d, 1.0));
        mat_free(&I);
    }

    /* det singular = 0 (rows are dependent) */
    {
        Matrix S; assert(mat_create(&S, 3, 3) == 0);
        const double v[] = {
            1, 2, 3,
            2, 4, 6,
            1, 1, 1
        };
        set_from(&S, v);
        double d = 0.0;
        assert(mat_det(&S, &d, EPS) == 0);
        assert(deq(d, 0.0));
        mat_free(&S);
    }

    /* rank: full row-rank 2x3 -> 2 */
    {
        Matrix R; assert(mat_create(&R, 2, 3) == 0);
        const double v[] = {1, 2, 3,
                            4, 5, 6};
        set_from(&R, v);
        size_t rk = 0;
        assert(mat_rank(&R, &rk, EPS) == 0);
        assert(rk == 2);
        mat_free(&R);
    }

    /* rank: dependent rows 2x3 -> 1 */
    {
        Matrix R; assert(mat_create(&R, 2, 3) == 0);
        const double v[] = {1, 2, 3,
                            2, 4, 6}; /* row2 = 2*row1 */
        set_from(&R, v);
        size_t rk = 0;
        assert(mat_rank(&R, &rk, EPS) == 0);
        assert(rk == 1);
        mat_free(&R);
    }

    return 0;
}
