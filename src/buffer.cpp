#include "buffer.h"

#include <sstream>

std::string Buffer::describe() const {
  std::stringstream ss;
  ss << "Buffer(" << size << ")";
  return ss.str();
}

