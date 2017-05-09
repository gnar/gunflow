#include "shape.h"

#include <sstream>

std::string Shape::describe() const {
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
