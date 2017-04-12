#include "ndarray.h"

void NDArray::describe(std::ostream &out) const {
  out << "NDArray(";
  out << "dtype=" << dtype << ", ";
  out << "shape=" << shape.describe() << ", ";
  out << "strides=" << strides.describe() << ", ";
  out << "buffer=" << buffer->describe() << ")";
}

