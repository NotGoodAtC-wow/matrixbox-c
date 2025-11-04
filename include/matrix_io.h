#ifndef MATRIX_IO_H
#define MATRIX_IO_H

#include <stdio.h>
#include "matrix.h"

/* Text format:
   First line: "<rows> <cols>\n"
   Then 'rows' lines with 'cols' space-separated numbers.
   Example:
     2 3
     1 2 3
     4 5 6
*/

int mat_read(FILE* fp, Matrix* out);                      // 0 ok; -1 bad args; -2 parse error
int mat_write(FILE* fp, const Matrix* m);                 // 0 ok; -1 bad args

int mat_read_file(const char* path, Matrix* out);         // 0 ok; <0 on error
int mat_write_file(const char* path, const Matrix* m);    // 0 ok; <0 on error

#endif /* MATRIX_IO_H */
