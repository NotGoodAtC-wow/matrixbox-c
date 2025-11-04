#include "matrix_io.h"

int mat_read(FILE* fp, Matrix* out) {
    if (!fp || !out) return -1;
    size_t r = 0, c = 0;
    if (fscanf(fp, "%zu %zu", &r, &c) != 2) return -2;
    if (mat_create(out, r, c) != 0) return -2;

    for (size_t i = 0; i < r; ++i) {
        for (size_t j = 0; j < c; ++j) {
            double v;
            if (fscanf(fp, "%lf", &v) != 1) {
                mat_free(out);
                return -2;
            }
            mat_set(out, i, j, v);
        }
    }
    return 0;
}

int mat_write(FILE* fp, const Matrix* m) {
    if (!fp || !m) return -1;
    fprintf(fp, "%zu %zu\n", m->rows, m->cols);
    for (size_t i = 0; i < m->rows; ++i) {
        for (size_t j = 0; j < m->cols; ++j) {
            fprintf(fp, "%.*g", 10, mat_get(m, i, j));
            if (j + 1 < m->cols) fputc(' ', fp);
        }
        fputc('\n', fp);
    }
    return 0;
}

int mat_read_file(const char* path, Matrix* out) {
    if (!path || !out) return -1;
    FILE* f = fopen(path, "rb");
    if (!f) return -2;
    int rc = mat_read(f, out);
    fclose(f);
    return rc;
}

int mat_write_file(const char* path, const Matrix* m) {
    if (!path || !m) return -1;
    FILE* f = fopen(path, "wb");
    if (!f) return -2;
    int rc = mat_write(f, m);
    fclose(f);
    return rc;
}
