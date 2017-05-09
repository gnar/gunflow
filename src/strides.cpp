#include "shape.h"
#include "strides.h"

#include <sstream>

std::string Strides::describe() const {
  std::stringstream ss;
  ss << "(";
  for (int d = 0; d < ndim; ++d) {
    if (d > 0)
      ss << ", ";
    ss << vec[d];
  }
  ss << ")";
  return ss.str();
}

Strides Strides::column_major(const Shape &shape) {
  int strides_vec[MAX_DIM];

  for (int d = 0, tmp = 1; d < shape.ndim; ++d) {
    strides_vec[d] = tmp;
    tmp *= shape.vec[d];
  }

  return Strides(strides_vec, strides_vec + shape.ndim);
}

Strides Strides::row_major(const Shape &shape) {
  int strides_vec[MAX_DIM];

  for (int d = shape.ndim - 1, tmp = 1; d >= 0; --d) {
    strides_vec[d] = tmp;
    tmp *= shape.vec[d];
  }

  return Strides(strides_vec, strides_vec + shape.ndim);
}
