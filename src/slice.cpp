#include "slice.h"

#include <sstream>

std::string Slice::describe() const {
  std::stringstream ss;
  ss << x0 << ":" << x1;
  if (step != 1) {
    ss << ":" << step;
  }
  return ss.str();
}
