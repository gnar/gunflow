#include "shape.h"

#include <iostream>

void Shape::describe(std::ostream &out) const {
  out << "(";
  for (int d = 0; d < ndim; ++d) {
    if (d > 0) out << ", ";
    out << vec[d];
  }
  out << ")";
}

