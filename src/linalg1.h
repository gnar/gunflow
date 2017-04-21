#ifndef LINALG1_H
#define LINALG1_H

#include "ndarray.h"
#include "util.h"

void fill(NDArray A, float v); // A <- v
void scale(NDArray A, float s); // A <- A*s

void add(NDArray A, NDArray B); // A <- A + B
void sub(NDArray A, NDArray B); // A <- A - B

void normal(NDArray A, float mean, float stddev); // A <- p(normal(mean, stddev))

#endif

