#ifndef LINALG_H
#define LINALG_H

#include "ndarray.h"

NDArray ones(Shape shape, float value=1.0);
NDArray zeros(Shape shape);
NDArray urand(Shape shape);
NDArray eye(int nrows, int ncols);

void matmul(NDArray C, NDArray A, NDArray B); // C <- A*B

#endif

