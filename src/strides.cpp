#include "strides.h"
#include "shape.h"

#include <iostream>

void Strides::describe(std::ostream &out) const {
  out << "(";
  for (int d = 0; d < ndim; ++d) {
    if (d > 0) out << ", ";
    out << vec[d];
  }
  out << ")";
}

Strides Strides::column_major(const Shape &shape, int dtype_stride) {
  int strides_vec[MAX_DIM];

  for (int d=0, tmp=dtype_stride; d<shape.ndim; ++d) {
    strides_vec[d] = tmp;
    tmp *= shape.vec[d];
  }

  return Strides(strides_vec, strides_vec + shape.ndim);
}

Strides Strides::row_major(const Shape &shape, int dtype_stride) {
  int strides_vec[MAX_DIM];

  for (int d=shape.ndim-1, tmp=dtype_stride; d>=0; --d) {
    strides_vec[d] = tmp;
    tmp *= shape.vec[d];
  }

  return Strides(strides_vec, strides_vec + shape.ndim);
}


