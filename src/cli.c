#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "matrix.h"
#include "matrix_io.h"

static void usage(void) {
    puts("matrixlab — simple CLI\n"
         "Usage:\n"
         "  matrixlab det    <A.txt>\n"
         "  matrixlab rank   <A.txt>\n"
         "  matrixlab trans  <A.txt> [OUT.txt]\n"
         "  matrixlab mul    <A.txt> <B.txt> [OUT.txt]\n"
         "  matrixlab add    <A.txt> <B.txt> [OUT.txt]\n"
         "  matrixlab sub    <A.txt> <B.txt> [OUT.txt]\n"
         "File format:\n"
         "  rows cols\\n  then 'rows' lines of 'cols' numbers.\n");
}

static int print_matrix_or_save(const Matrix* M, const char* out_path) {
    if (out_path) return mat_write_file(out_path, M);
    return mat_write(stdout, M);
}

int main(int argc, char** argv) {
    if (argc < 3) { usage(); return 1; }

    const char* cmd = argv[1];
    const double EPS = 1e-9;

    if (strcmp(cmd, "det") == 0) {
        if (argc != 3) { usage(); return 2; }
        Matrix A; if (mat_read_file(argv[2], &A) != 0) { perror("read"); return 3; }
        double d = 0.0;
        int rc = mat_det(&A, &d, EPS);
        mat_free(&A);
        if (rc == -2) { fprintf(stderr, "error: matrix must be square\n"); return 4; }
        if (rc != 0)  { fprintf(stderr, "error: det failed (rc=%d)\n", rc); return 5; }
        printf("det: %.10g\n", d);
        return 0;
    }

    if (strcmp(cmd, "rank") == 0) {
        if (argc != 3) { usage(); return 2; }
        Matrix A; if (mat_read_file(argv[2], &A) != 0) { perror("read"); return 3; }
        size_t rk = 0;
        int rc = mat_rank(&A, &rk, EPS);
        mat_free(&A);
        if (rc != 0) { fprintf(stderr, "error: rank failed (rc=%d)\n", rc); return 5; }
        printf("rank: %zu\n", rk);
        return 0;
    }

    if (strcmp(cmd, "trans") == 0) {
        if (argc != 3 && argc != 4) { usage(); return 2; }
        const char* in  = argv[2];
        const char* out = (argc == 4 ? argv[3] : NULL);

        Matrix A; if (mat_read_file(in, &A) != 0) { perror("read"); return 3; }
        Matrix T; if (mat_create(&T, A.cols, A.rows) != 0) { mat_free(&A); return 6; }
        if (mat_transpose(&A, &T) != 0) { mat_free(&A); mat_free(&T); return 5; }

        int rc = print_matrix_or_save(&T, out);
        mat_free(&A); mat_free(&T);
        return (rc == 0) ? 0 : 7;
    }

    if (strcmp(cmd, "mul") == 0 || strcmp(cmd, "add") == 0 || strcmp(cmd, "sub") == 0) {
        if (argc != 4 && argc != 5) { usage(); return 2; }
        const char* Apath = argv[2];
        const char* Bpath = argv[3];
        const char* out   = (argc == 5 ? argv[4] : NULL);

        Matrix A, B;
        if (mat_read_file(Apath, &A) != 0) { perror("read A"); return 3; }
        if (mat_read_file(Bpath, &B) != 0) { mat_free(&A); perror("read B"); return 3; }

        Matrix C;
        if (strcmp(cmd, "mul") == 0) {
            if (mat_create(&C, A.rows, B.cols) != 0) { mat_free(&A); mat_free(&B); return 6; }
            int rc = mat_mul(&A, &B, &C);
            if (rc != 0) { fprintf(stderr, "mul error rc=%d\n", rc); mat_free(&A); mat_free(&B); mat_free(&C); return 5; }
        } else {
            if (A.rows != B.rows || A.cols != B.cols) {
                fprintf(stderr, "error: shapes must match for add/sub\n");
                mat_free(&A); mat_free(&B); return 4;
            }
            if (mat_create(&C, A.rows, A.cols) != 0) { mat_free(&A); mat_free(&B); return 6; }
            int rc = (strcmp(cmd, "add") == 0) ? mat_add(&A, &B, &C) : mat_sub(&A, &B, &C);
            if (rc != 0) { fprintf(stderr, "add/sub error rc=%d\n", rc); mat_free(&A); mat_free(&B); mat_free(&C); return 5; }
        }

        int wrc = print_matrix_or_save(&C, out);
        mat_free(&A); mat_free(&B); mat_free(&C);
        return (wrc == 0) ? 0 : 7;
    }

    usage();
    return 1;
}
