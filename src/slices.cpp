#include "slices.h"

#include <sstream>

std::string Slices::describe() const {
  std::stringstream ss;
  for (auto i=0u; i<vec.size(); ++i) {
    if (i > 0) ss << ",";
    ss << vec[i].describe();
  }
  return ss.str();
}

